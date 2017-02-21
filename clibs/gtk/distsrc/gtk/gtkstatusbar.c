/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 * GtkStatusbar Copyright (C) 1998 Shawn T. Amundson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/.
 */

#include "config.h"

#include "gtkstatusbar.h"

#include "gtkboxprivate.h"
#include "gtkframe.h"
#include "gtklabel.h"
#include "gtkmarshalers.h"
#include "gtkwindow.h"
#include "gtkprivate.h"
#include "gtkintl.h"
#include "gtkorientable.h"
#include "gtktypebuiltins.h"
#include "a11y/gtkstatusbaraccessible.h"

/**
 * SECTION:gtkstatusbar
 * @title: GtkStatusbar
 * @short_description: Report messages of minor importance to the user
 *
 * A #GtkStatusbar is usually placed along the bottom of an application's
 * main #GtkWindow. It may provide a regular commentary of the application's
 * status (as is usually the case in a web browser, for example), or may be
 * used to simply output a message when the status changes, (when an upload
 * is complete in an FTP client, for example).
 *
 * Status bars in GTK+ maintain a stack of messages. The message at
 * the top of the each bar’s stack is the one that will currently be displayed.
 *
 * Any messages added to a statusbar’s stack must specify a
 * context id that is used to uniquely identify
 * the source of a message. This context id can be generated by
 * gtk_statusbar_get_context_id(), given a message and the statusbar that
 * it will be added to. Note that messages are stored in a stack, and when
 * choosing which message to display, the stack structure is adhered to,
 * regardless of the context identifier of a message.
 *
 * One could say that a statusbar maintains one stack of messages for
 * display purposes, but allows multiple message producers to maintain
 * sub-stacks of the messages they produced (via context ids).
 *
 * Status bars are created using gtk_statusbar_new().
 *
 * Messages are added to the bar’s stack with gtk_statusbar_push().
 *
 * The message at the top of the stack can be removed using
 * gtk_statusbar_pop(). A message can be removed from anywhere in the
 * stack if its message id was recorded at the time it was added. This
 * is done using gtk_statusbar_remove().
 */
typedef struct _GtkStatusbarMsg GtkStatusbarMsg;

struct _GtkStatusbarPrivate
{
  GtkWidget     *frame;
  GtkWidget     *label;
  GtkWidget     *message_area;

  GSList        *messages;
  GSList        *keys;

  guint          seq_context_id;
  guint          seq_message_id;
};


struct _GtkStatusbarMsg
{
  gchar *text;
  guint context_id;
  guint message_id;
};

enum
{
  SIGNAL_TEXT_PUSHED,
  SIGNAL_TEXT_POPPED,
  SIGNAL_LAST
};

static void     gtk_statusbar_update            (GtkStatusbar      *statusbar,
						 guint              context_id,
						 const gchar       *text);
static void     gtk_statusbar_realize           (GtkWidget         *widget);
static void     gtk_statusbar_destroy           (GtkWidget         *widget);
static void     gtk_statusbar_size_allocate     (GtkWidget         *widget,
                                                 GtkAllocation     *allocation);
static void     gtk_statusbar_hierarchy_changed (GtkWidget         *widget,
                                                 GtkWidget         *previous_toplevel);


static guint              statusbar_signals[SIGNAL_LAST] = { 0 };

G_DEFINE_TYPE_WITH_PRIVATE (GtkStatusbar, gtk_statusbar, GTK_TYPE_BOX)

static void
gtk_statusbar_class_init (GtkStatusbarClass *class)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (class);

  widget_class->realize = gtk_statusbar_realize;
  widget_class->destroy = gtk_statusbar_destroy;
  widget_class->size_allocate = gtk_statusbar_size_allocate;
  widget_class->hierarchy_changed = gtk_statusbar_hierarchy_changed;

  class->text_pushed = gtk_statusbar_update;
  class->text_popped = gtk_statusbar_update;

  /**
   * GtkStatusbar::text-pushed:
   * @statusbar: the object which received the signal
   * @context_id: the context id of the relevant message/statusbar
   * @text: the message that was pushed
   *
   * Is emitted whenever a new message gets pushed onto a statusbar's stack.
   */
  statusbar_signals[SIGNAL_TEXT_PUSHED] =
    g_signal_new (I_("text-pushed"),
		  G_OBJECT_CLASS_TYPE (class),
		  G_SIGNAL_RUN_LAST,
		  G_STRUCT_OFFSET (GtkStatusbarClass, text_pushed),
		  NULL, NULL,
		  _gtk_marshal_VOID__UINT_STRING,
		  G_TYPE_NONE, 2,
		  G_TYPE_UINT,
		  G_TYPE_STRING);

  /**
   * GtkStatusbar::text-popped:
   * @statusbar: the object which received the signal
   * @context_id: the context id of the relevant message/statusbar
   * @text: the message that was just popped
   *
   * Is emitted whenever a new message is popped off a statusbar's stack.
   */
  statusbar_signals[SIGNAL_TEXT_POPPED] =
    g_signal_new (I_("text-popped"),
		  G_OBJECT_CLASS_TYPE (class),
		  G_SIGNAL_RUN_LAST,
		  G_STRUCT_OFFSET (GtkStatusbarClass, text_popped),
		  NULL, NULL,
		  _gtk_marshal_VOID__UINT_STRING,
		  G_TYPE_NONE, 2,
		  G_TYPE_UINT,
		  G_TYPE_STRING);

  gtk_widget_class_install_style_property (widget_class,
                                           g_param_spec_enum ("shadow-type",
                                                              P_("Shadow type"),
                                                              P_("Style of bevel around the statusbar text"),
                                                              GTK_TYPE_SHADOW_TYPE,
                                                              GTK_SHADOW_IN,
                                                              GTK_PARAM_READABLE));

  /* Bind class to template
   */
  gtk_widget_class_set_template_from_resource (widget_class, "/org/gtk/libgtk/ui/gtkstatusbar.ui");
  gtk_widget_class_bind_template_child_internal_private (widget_class, GtkStatusbar, message_area);
  gtk_widget_class_bind_template_child_private (widget_class, GtkStatusbar, frame);
  gtk_widget_class_bind_template_child_private (widget_class, GtkStatusbar, label);

  gtk_widget_class_set_accessible_type (widget_class, GTK_TYPE_STATUSBAR_ACCESSIBLE);
}

static void
gtk_statusbar_init (GtkStatusbar *statusbar)
{
  GtkStatusbarPrivate *priv;
  GtkShadowType shadow_type;

  statusbar->priv = gtk_statusbar_get_instance_private (statusbar);
  priv = statusbar->priv;

  priv->seq_context_id = 1;
  priv->seq_message_id = 1;
  priv->messages = NULL;
  priv->keys = NULL;

  gtk_widget_init_template (GTK_WIDGET (statusbar));

  gtk_widget_set_redraw_on_allocate (GTK_WIDGET (statusbar), TRUE);
  gtk_widget_style_get (GTK_WIDGET (statusbar), "shadow-type", &shadow_type, NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (priv->frame), shadow_type);
}

/**
 * gtk_statusbar_new:
 *
 * Creates a new #GtkStatusbar ready for messages.
 *
 * Returns: the new #GtkStatusbar
 */
GtkWidget* 
gtk_statusbar_new (void)
{
  return g_object_new (GTK_TYPE_STATUSBAR, NULL);
}

static void
gtk_statusbar_update (GtkStatusbar *statusbar,
		      guint	    context_id,
		      const gchar  *text)
{
  GtkStatusbarPrivate *priv;

  g_return_if_fail (GTK_IS_STATUSBAR (statusbar));

  priv = statusbar->priv;

  if (!text)
    text = "";

  gtk_label_set_text (GTK_LABEL (priv->label), text);
}

/**
 * gtk_statusbar_get_context_id:
 * @statusbar: a #GtkStatusbar
 * @context_description: textual description of what context 
 *                       the new message is being used in
 *
 * Returns a new context identifier, given a description 
 * of the actual context. Note that the description is 
 * not shown in the UI.
 *
 * Returns: an integer id
 */
guint
gtk_statusbar_get_context_id (GtkStatusbar *statusbar,
			      const gchar  *context_description)
{
  GtkStatusbarPrivate *priv;
  gchar *string;
  guint id;
  
  g_return_val_if_fail (GTK_IS_STATUSBAR (statusbar), 0);
  g_return_val_if_fail (context_description != NULL, 0);

  priv = statusbar->priv;

  /* we need to preserve namespaces on object datas */
  string = g_strconcat ("gtk-status-bar-context:", context_description, NULL);

  id = GPOINTER_TO_UINT (g_object_get_data (G_OBJECT (statusbar), string));
  if (id == 0)
    {
      id = priv->seq_context_id++;
      g_object_set_data_full (G_OBJECT (statusbar), string, GUINT_TO_POINTER (id), NULL);
      priv->keys = g_slist_prepend (priv->keys, string);
    }
  else
    g_free (string);

  return id;
}

static GtkStatusbarMsg *
gtk_statusbar_msg_create (GtkStatusbar *statusbar,
		          guint         context_id,
		          const gchar  *text)
{
  GtkStatusbarMsg *msg;

  msg = g_slice_new (GtkStatusbarMsg);
  msg->text = g_strdup (text);
  msg->context_id = context_id;
  msg->message_id = statusbar->priv->seq_message_id++;

  return msg;
}

static void
gtk_statusbar_msg_free (GtkStatusbarMsg *msg)
{
  g_free (msg->text);
  g_slice_free (GtkStatusbarMsg, msg);
}

/**
 * gtk_statusbar_push:
 * @statusbar: a #GtkStatusbar
 * @context_id: the message’s context id, as returned by
 *              gtk_statusbar_get_context_id()
 * @text: the message to add to the statusbar
 * 
 * Pushes a new message onto a statusbar’s stack.
 *
 * Returns: a message id that can be used with 
 *          gtk_statusbar_remove().
 */
guint
gtk_statusbar_push (GtkStatusbar *statusbar,
		    guint	  context_id,
		    const gchar  *text)
{
  GtkStatusbarPrivate *priv;
  GtkStatusbarMsg *msg;

  g_return_val_if_fail (GTK_IS_STATUSBAR (statusbar), 0);
  g_return_val_if_fail (text != NULL, 0);

  priv = statusbar->priv;

  msg = gtk_statusbar_msg_create (statusbar, context_id, text);
  priv->messages = g_slist_prepend (priv->messages, msg);

  g_signal_emit (statusbar,
		 statusbar_signals[SIGNAL_TEXT_PUSHED],
		 0,
		 msg->context_id,
		 msg->text);

  return msg->message_id;
}

/**
 * gtk_statusbar_pop:
 * @statusbar: a #GtkStatusbar
 * @context_id: a context identifier
 * 
 * Removes the first message in the #GtkStatusbar’s stack
 * with the given context id. 
 *
 * Note that this may not change the displayed message, if 
 * the message at the top of the stack has a different 
 * context id.
 */
void
gtk_statusbar_pop (GtkStatusbar *statusbar,
		   guint	 context_id)
{
  GtkStatusbarPrivate *priv;
  GtkStatusbarMsg *msg;

  g_return_if_fail (GTK_IS_STATUSBAR (statusbar));

  priv = statusbar->priv;

  if (priv->messages)
    {
      GSList *list;

      for (list = priv->messages; list; list = list->next)
	{
	  msg = list->data;

	  if (msg->context_id == context_id)
	    {
	      priv->messages = g_slist_remove_link (priv->messages, list);
	      gtk_statusbar_msg_free (msg);
	      g_slist_free_1 (list);
	      break;
	    }
	}
    }

  msg = priv->messages ? priv->messages->data : NULL;

  g_signal_emit (statusbar,
		 statusbar_signals[SIGNAL_TEXT_POPPED],
		 0,
		 (guint) (msg ? msg->context_id : 0),
		 msg ? msg->text : NULL);
}

/**
 * gtk_statusbar_remove:
 * @statusbar: a #GtkStatusbar
 * @context_id: a context identifier
 * @message_id: a message identifier, as returned by gtk_statusbar_push()
 *
 * Forces the removal of a message from a statusbar’s stack. 
 * The exact @context_id and @message_id must be specified.
 */
void
gtk_statusbar_remove (GtkStatusbar *statusbar,
		      guint	   context_id,
		      guint        message_id)
{
  GtkStatusbarPrivate *priv;
  GtkStatusbarMsg *msg;

  g_return_if_fail (GTK_IS_STATUSBAR (statusbar));
  g_return_if_fail (message_id > 0);

  priv = statusbar->priv;

  msg = priv->messages ? priv->messages->data : NULL;
  if (msg)
    {
      GSList *list;

      /* care about signal emission if the topmost item is removed */
      if (msg->context_id == context_id &&
	  msg->message_id == message_id)
	{
	  gtk_statusbar_pop (statusbar, context_id);
	  return;
	}
      
      for (list = priv->messages; list; list = list->next)
	{
	  msg = list->data;
	  
	  if (msg->context_id == context_id &&
	      msg->message_id == message_id)
	    {
	      priv->messages = g_slist_remove_link (priv->messages, list);
	      gtk_statusbar_msg_free (msg);
	      g_slist_free_1 (list);
	      
	      break;
	    }
	}
    }
}

/**
 * gtk_statusbar_remove_all:
 * @statusbar: a #GtkStatusbar
 * @context_id: a context identifier
 *
 * Forces the removal of all messages from a statusbar's
 * stack with the exact @context_id.
 *
 * Since: 2.22
 */
void
gtk_statusbar_remove_all (GtkStatusbar *statusbar,
                          guint         context_id)
{
  GtkStatusbarPrivate *priv;
  GtkStatusbarMsg *msg;
  GSList *prev, *list;

  g_return_if_fail (GTK_IS_STATUSBAR (statusbar));

  priv = statusbar->priv;

  if (priv->messages == NULL)
    return;

  msg = priv->messages->data;

  /* care about signal emission if the topmost item is removed */
  if (msg->context_id == context_id)
    {
      gtk_statusbar_pop (statusbar, context_id);

      prev = NULL;
      list = priv->messages;
    }
  else
    {
      prev = priv->messages;
      list = prev->next;
    }

  while (list != NULL)
    {
      msg = list->data;

      if (msg->context_id == context_id)
        {
          if (prev == NULL)
            priv->messages = list->next;
          else
            prev->next = list->next;

          gtk_statusbar_msg_free (msg);
          g_slist_free_1 (list);

          if (prev == NULL)
            prev = priv->messages;

          if (prev)
            list = prev->next;
          else
            list = NULL;
        }
      else
        {
          prev = list;
          list = prev->next;
        }
    }
}

/**
 * gtk_statusbar_get_message_area:
 * @statusbar: a #GtkStatusbar
 *
 * Retrieves the box containing the label widget.
 *
 * Returns: (transfer none): a #GtkBox
 *
 * Since: 2.20
 */
GtkWidget*
gtk_statusbar_get_message_area (GtkStatusbar *statusbar)
{
  GtkStatusbarPrivate *priv;

  g_return_val_if_fail (GTK_IS_STATUSBAR (statusbar), NULL);

  priv = statusbar->priv;

  return priv->message_area;
}

static void
gtk_statusbar_destroy (GtkWidget *widget)
{
  GtkStatusbar *statusbar = GTK_STATUSBAR (widget);
  GtkStatusbarPrivate *priv = statusbar->priv;

  g_slist_free_full (priv->messages, (GDestroyNotify) gtk_statusbar_msg_free);
  priv->messages = NULL;

  g_slist_free_full (priv->keys, g_free);
  priv->keys = NULL;

  GTK_WIDGET_CLASS (gtk_statusbar_parent_class)->destroy (widget);
}

/* look for extra children between the frame containing
 * the label and where we want to draw the resize grip
 */
static gboolean
has_extra_children (GtkStatusbar *statusbar)
{
  GtkStatusbarPrivate *priv = statusbar->priv;
  GtkPackType child_pack_type, frame_pack_type;
  GtkWidget *child, *frame;
  GList *l, *children;
  gboolean retval = FALSE;

  frame = NULL;
  children = _gtk_box_get_children (GTK_BOX (statusbar));
  for (l = children; l; l = l->next)
    {
      frame = l->data;

      if (frame == priv->frame)
        break;
    }

  gtk_box_query_child_packing (GTK_BOX (statusbar), frame,
                               NULL, NULL, NULL, &frame_pack_type);

  for (l = l->next; l; l = l->next)
    {
      child = l->data;

      if (!gtk_widget_get_visible (child))
        continue;

      gtk_box_query_child_packing (GTK_BOX (statusbar), child,
                                   NULL, NULL, NULL, &child_pack_type);

      if (frame_pack_type == GTK_PACK_START || child_pack_type == GTK_PACK_END)
        {
          retval = TRUE;
          break;
        }
    }

  g_list_free (children);

  return retval;
}

static void
gtk_statusbar_size_allocate (GtkWidget     *widget,
                             GtkAllocation *allocation)
{
  GtkStatusbar *statusbar = GTK_STATUSBAR (widget);
  GtkStatusbarPrivate *priv = statusbar->priv;
  gboolean extra_children = FALSE;
  gboolean has_resize_grip = FALSE;
  GdkRectangle rect;
  GtkWidget *window;
  gint x, y;
  GdkRectangle translated_rect;

  window = gtk_widget_get_toplevel (widget);

  if (GTK_IS_WINDOW (window) &&
      gtk_window_resize_grip_is_visible (GTK_WINDOW (window)))
    {
      gtk_window_get_resize_grip_area (GTK_WINDOW (window), &rect);
      if (gtk_widget_translate_coordinates (widget, window, 0, 0, &x, &y))
        {
          translated_rect.x = x;
          translated_rect.y = y;
          translated_rect.width = allocation->width;
          translated_rect.height = allocation->height;

          if (gdk_rectangle_intersect (&rect, &translated_rect, NULL))
            {
              has_resize_grip = TRUE;
              extra_children = has_extra_children (statusbar);

              /* If there are extra children, we don't want them to occupy
               * the space where we draw the resize grip, so we temporarily
               * shrink the allocation.
               * If there are no extra children, we want the frame to get
               * the full allocation, and we fix up the allocation of the
               * label afterwards to make room for the grip.
               */
              if (extra_children)
                {
                  allocation->width -= rect.width;
                  if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL)
                    allocation->x += rect.width;
                }
            }
        }
    }

  /* chain up normally */
  GTK_WIDGET_CLASS (gtk_statusbar_parent_class)->size_allocate (widget, allocation);

  if (has_resize_grip)
    {
      if (extra_children)
        {
          allocation->width += rect.width;
          if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL)
            allocation->x -= rect.width;

          gtk_widget_set_allocation (widget, allocation);
        }
      else
        {
          GtkAllocation child_allocation, frame_allocation;
          GtkWidget *child;

          /* Use the frame's child instead of statusbar->label directly, in case
           * the label has been replaced by a container as the frame's child
           * (and the label reparented into that container).
           */
          child = gtk_bin_get_child (GTK_BIN (priv->frame));

          gtk_widget_get_allocation (child, &child_allocation);
          gtk_widget_get_allocation (priv->frame, &frame_allocation);
          if (child_allocation.width + rect.width > frame_allocation.width)
            {
              /* shrink the label to make room for the grip */
              *allocation = child_allocation;
              allocation->width = MAX (1, allocation->width - rect.width);
              if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL)
                allocation->x += child_allocation.width - allocation->width;

              gtk_widget_size_allocate (child, allocation);
            }
        }
    }
}

static void
resize_grip_visible_changed (GObject    *object,
                             GParamSpec *pspec,
                             gpointer    user_data)
{
  GtkStatusbar *statusbar = GTK_STATUSBAR (user_data);
  GtkStatusbarPrivate *priv = statusbar->priv;

  gtk_widget_queue_resize (priv->label);
  gtk_widget_queue_resize (priv->frame);
  gtk_widget_queue_resize (GTK_WIDGET (statusbar));
}

static void
gtk_statusbar_hierarchy_changed (GtkWidget *widget,
                                 GtkWidget *previous_toplevel)
{
  GtkWidget *window;

  if (previous_toplevel)
    g_signal_handlers_disconnect_by_func (previous_toplevel,
                                          G_CALLBACK (resize_grip_visible_changed),
                                          widget);
  window = gtk_widget_get_toplevel (widget);
  if (GTK_IS_WINDOW (window))
    g_signal_connect (window, "notify::resize-grip-visible",
                      G_CALLBACK (resize_grip_visible_changed), widget);

  resize_grip_visible_changed (NULL, NULL, widget);
}

static void
gtk_statusbar_realize (GtkWidget *widget)
{
  GTK_WIDGET_CLASS (gtk_statusbar_parent_class)->realize (widget);

  resize_grip_visible_changed (NULL, NULL, widget);
}
