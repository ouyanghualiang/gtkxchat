// Copyright 2014-2015 The GTK+Android Developers. See the COPYRIGHT
// file at the top-level directory of this distribution and at
// https://github.com/eugals/GTKAndroid/wiki/COPYRIGHT.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.
//
// Author(s): Evgeny Sologubov
//
// GTK+Android test application

#include <jni.h>
#include <errno.h>

#include <android_native_app_glue.h>
#include <android/log.h>
#include <gtkandroid.h>

#define SERVLIST_X_PADDING 4			/* horizontal paddig in the network editor */
#define SERVLIST_Y_PADDING 0			/* vertical padding in the network editor */

/* servlistgui.c globals */
static GtkWidget *serverlist_win = NULL;
static GtkWidget *networks_tree;		/* network TreeView */

static int netlist_win_width = 0;		/* don't hardcode pixels, just use as much as needed by default, save if resized */
static int netlist_win_height = 0;
static int netedit_win_width = 0;
static int netedit_win_height = 0;

static int netedit_active_tab = 0;

/* global user info */
static GtkWidget *entry_nick1;
static GtkWidget *entry_nick2;
static GtkWidget *entry_nick3;
static GtkWidget *entry_guser;
/* static GtkWidget *entry_greal; */

enum {
		SERVER_TREE,
		CHANNEL_TREE,
		CMD_TREE,
		N_TREES,
};

/* edit area */
static GtkWidget *edit_win;
static GtkWidget *edit_entry_nick;
static GtkWidget *edit_entry_nick2;
static GtkWidget *edit_entry_user;
static GtkWidget *edit_entry_real;
static GtkWidget *edit_entry_pass;
static GtkWidget *edit_label_nick;
static GtkWidget *edit_label_nick2;
static GtkWidget *edit_label_real;
static GtkWidget *edit_label_user;
static GtkWidget *edit_trees[N_TREES];


static void hello(GtkWidget *widget, gpointer data)
{
    GtkWidget *box = (GtkWidget *) data;
    GtkWidget *label = gtk_label_new("Hello!");
    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_widget_show(label);
}

static void quit_gtk(GtkWidget *widget, gpointer data)
{
    g_info("quit!");
    gtk_main_quit();
}



static GtkWidget *
bold_label (char *text)
{
	char buf[128];
	GtkWidget *label;

	g_snprintf (buf, sizeof (buf), "<b>%s</b>", text);
	label = gtk_label_new (buf);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_widget_show (label);

	return label;
}




void android_main(struct android_app *state)
{
    GtkWidget *servlist;
	GtkWidget *vbox1;
	GtkWidget *label2;
	GtkWidget *table1;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *label5;
	GtkWidget *label6;
	/* GtkWidget *label7; */
	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *entry3;
	GtkWidget *entry4;
	/* GtkWidget *entry5; */
	GtkWidget *vbox2;
	GtkWidget *label1;
	GtkWidget *table4;
	GtkWidget *scrolledwindow3;
	GtkWidget *treeview_networks;
	GtkWidget *checkbutton_skip;
	GtkWidget *checkbutton_fav;
	GtkWidget *hbox;
	GtkWidget *vbuttonbox2;
	GtkWidget *button_add;
	GtkWidget *button_remove;
	GtkWidget *button_edit;
	GtkWidget *button_sort;
	GtkWidget *hseparator1;
	GtkWidget *hbuttonbox1;
	GtkWidget *button_connect;
	GtkWidget *button_close;
	GtkTreeModel *model;
	GtkListStore *store;
	GtkCellRenderer *renderer;

    //g_usleep(3 * 1000000);
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
    gtk_android_init(state);
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);

    servlist = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width (GTK_CONTAINER (servlist), 4);
	gtk_window_set_title (GTK_WINDOW (servlist), ("DISPLAY_NAME: Network List"));
	gtk_window_set_default_size (GTK_WINDOW (servlist), 0,0);
	gtk_window_set_role (GTK_WINDOW (servlist), "servlist");
	gtk_window_set_type_hint (GTK_WINDOW (servlist), GDK_WINDOW_TYPE_HINT_DIALOG);

	vbox1 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox1);
	gtk_container_add (GTK_CONTAINER (servlist), vbox1);

	label2 = bold_label (("User Information"));
	gtk_box_pack_start (GTK_BOX (vbox1), label2, FALSE, FALSE, 0);

	table1 = gtk_table_new (5, 2, FALSE);
	gtk_widget_show (table1);
	gtk_box_pack_start (GTK_BOX (vbox1), table1, FALSE, FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (table1), 8);
	gtk_table_set_row_spacings (GTK_TABLE (table1), 2);
	gtk_table_set_col_spacings (GTK_TABLE (table1), 4);

	label3 = gtk_label_new_with_mnemonic (("_Nick name:"));
	gtk_widget_show (label3);
	gtk_table_attach (GTK_TABLE (table1), label3, 0, 1, 0, 1,
							(GtkAttachOptions) (GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label3), 0, 0.5);

	label4 = gtk_label_new (("Second choice:"));
	gtk_widget_show (label4);
	gtk_table_attach (GTK_TABLE (table1), label4, 0, 1, 1, 2,
							(GtkAttachOptions) (GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label4), 0, 0.5);

	label5 = gtk_label_new (("Third choice:"));
	gtk_widget_show (label5);
	gtk_table_attach (GTK_TABLE (table1), label5, 0, 1, 2, 3,
							(GtkAttachOptions) (GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label5), 0, 0.5);

	label6 = gtk_label_new_with_mnemonic (("_User name:"));
	gtk_widget_show (label6);
	gtk_table_attach (GTK_TABLE (table1), label6, 0, 1, 3, 4,
							(GtkAttachOptions) (GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label6), 0, 0.5);

	/* label7 = gtk_label_new_with_mnemonic (_("Rea_l name:"));
	gtk_widget_show (label7);
	gtk_table_attach (GTK_TABLE (table1), label7, 0, 1, 4, 5,
							(GtkAttachOptions) (GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label7), 0, 0.5);*/

	entry_nick1 = entry1 = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (entry1), "ouyang");//输入框文本
	gtk_widget_show (entry1);
	gtk_table_attach (GTK_TABLE (table1), entry1, 1, 2, 0, 1,
							(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);

	entry_nick2 = entry2 = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (entry2), "ouyang_");
	gtk_widget_show (entry2);
	gtk_table_attach (GTK_TABLE (table1), entry2, 1, 2, 1, 2,
							(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);

	entry_nick3 = entry3 = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (entry3), "prefs.hex_irc_nick3");
	gtk_widget_show (entry3);
	gtk_table_attach (GTK_TABLE (table1), entry3, 1, 2, 2, 3,
							(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);

	entry_guser = entry4 = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (entry4), "prefs.hex_irc_user_name");
	gtk_widget_show (entry4);
	gtk_table_attach (GTK_TABLE (table1), entry4, 1, 2, 3, 4,
							(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);

	/* entry_greal = entry5 = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (entry5), prefs.hex_irc_real_name);
	gtk_widget_show (entry5);
	gtk_table_attach (GTK_TABLE (table1), entry5, 1, 2, 4, 5,
							(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
							(GtkAttachOptions) (0), 0, 0); */
    
    vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox2);
	gtk_box_pack_start (GTK_BOX (vbox1), vbox2, TRUE, TRUE, 0);

	label1 = bold_label (("Networks"));
	gtk_box_pack_start (GTK_BOX (vbox2), label1, FALSE, FALSE, 0);

	table4 = gtk_table_new (2, 2, FALSE);
	gtk_widget_show (table4);
	gtk_box_pack_start (GTK_BOX (vbox2), table4, TRUE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (table4), 8);
	gtk_table_set_row_spacings (GTK_TABLE (table4), 2);
	gtk_table_set_col_spacings (GTK_TABLE (table4), 3);
/*
	scrolledwindow3 = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow3);
	gtk_table_attach (GTK_TABLE (table4), scrolledwindow3, 0, 1, 0, 1,
							(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
							(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow3),
											  GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow3),
													 GTK_SHADOW_IN);

	store = gtk_list_store_new (3, G_TYPE_STRING, G_TYPE_BOOLEAN, G_TYPE_INT);
	model = GTK_TREE_MODEL (store);

	networks_tree = treeview_networks = gtk_tree_view_new_with_model (model);
	g_object_unref (model);
	gtk_widget_show (treeview_networks);
	gtk_container_add (GTK_CONTAINER (scrolledwindow3), treeview_networks);
	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (treeview_networks),
												  FALSE);

	renderer = gtk_cell_renderer_text_new ();
	g_signal_connect (G_OBJECT (renderer), "edited",
							G_CALLBACK (servlist_celledit_cb), model);
	gtk_tree_view_insert_column_with_attributes (
								GTK_TREE_VIEW (treeview_networks), -1,
						 		0, renderer,
						 		"text", 0,
								"editable", 1,
								"weight", 2,
								NULL);

	hbox = gtk_hbox_new (0, FALSE);
	gtk_table_attach (GTK_TABLE (table4), hbox, 0, 2, 1, 2,
							(GtkAttachOptions) (GTK_FILL),
							(GtkAttachOptions) (0), 0, 0);
	gtk_widget_show (hbox);

	checkbutton_skip =
		gtk_check_button_new_with_mnemonic (_("Skip network list on startup"));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton_skip),
											prefs.hex_gui_slist_skip);
	gtk_container_add (GTK_CONTAINER (hbox), checkbutton_skip);
	g_signal_connect (G_OBJECT (checkbutton_skip), "toggled",
							G_CALLBACK (no_servlist), 0);
	gtk_widget_show (checkbutton_skip);

	checkbutton_fav =
		gtk_check_button_new_with_mnemonic (_("Show favorites only"));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton_fav),
											prefs.hex_gui_slist_fav);
	gtk_container_add (GTK_CONTAINER (hbox), checkbutton_fav);
	g_signal_connect (G_OBJECT (checkbutton_fav), "toggled",
							G_CALLBACK (fav_servlist), 0);
	gtk_widget_show (checkbutton_fav);

	vbuttonbox2 = gtk_vbutton_box_new ();
	gtk_box_set_spacing (GTK_BOX (vbuttonbox2), 3);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (vbuttonbox2), GTK_BUTTONBOX_START);
	gtk_widget_show (vbuttonbox2);
	gtk_table_attach (GTK_TABLE (table4), vbuttonbox2, 1, 2, 0, 1,
							(GtkAttachOptions) (GTK_FILL),
							(GtkAttachOptions) (GTK_FILL), 0, 0);

	button_add = gtk_button_new_from_stock ("gtk-add");
	g_signal_connect (G_OBJECT (button_add), "clicked",
							G_CALLBACK (servlist_addnet_cb), networks_tree);
	gtk_widget_show (button_add);
	gtk_container_add (GTK_CONTAINER (vbuttonbox2), button_add);
	gtk_widget_set_can_default (button_add, TRUE);

	button_remove = gtk_button_new_from_stock ("gtk-remove");
	g_signal_connect (G_OBJECT (button_remove), "clicked",
							G_CALLBACK (servlist_deletenet_cb), 0);
	gtk_widget_show (button_remove);
	gtk_container_add (GTK_CONTAINER (vbuttonbox2), button_remove);
	gtk_widget_set_can_default (button_remove, TRUE);

	button_edit = gtk_button_new_with_mnemonic (_("_Edit..."));
	g_signal_connect (G_OBJECT (button_edit), "clicked",
							G_CALLBACK (servlist_edit_cb), 0);
	gtk_widget_show (button_edit);
	gtk_container_add (GTK_CONTAINER (vbuttonbox2), button_edit);
	gtk_widget_set_can_default (button_edit, TRUE);

	button_sort = gtk_button_new_with_mnemonic (_("_Sort"));
	gtk_widget_set_tooltip_text (button_sort, _("Sorts the network list in alphabetical order. "
				"Use SHIFT-UP and SHIFT-DOWN keys to move a row."));
	g_signal_connect (G_OBJECT (button_sort), "clicked",
							G_CALLBACK (servlist_sort), 0);
	gtk_widget_show (button_sort);
	gtk_container_add (GTK_CONTAINER (vbuttonbox2), button_sort);
	gtk_widget_set_can_default (button_sort, TRUE);

	button_sort = gtk_button_new_with_mnemonic (_("_Favor"));
	gtk_widget_set_tooltip_text (button_sort, _("Mark or unmark this network as a favorite."));
	g_signal_connect (G_OBJECT (button_sort), "clicked",
							G_CALLBACK (servlist_favor), 0);
	gtk_widget_show (button_sort);
	gtk_container_add (GTK_CONTAINER (vbuttonbox2), button_sort);
	gtk_widget_set_can_default (button_sort, TRUE);

	hseparator1 = gtk_hseparator_new ();
	gtk_widget_show (hseparator1);
	gtk_box_pack_start (GTK_BOX (vbox1), hseparator1, FALSE, TRUE, 4);

	hbuttonbox1 = gtk_hbutton_box_new ();
	gtk_widget_show (hbuttonbox1);
	gtk_box_pack_start (GTK_BOX (vbox1), hbuttonbox1, FALSE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (hbuttonbox1), 8);

	button_close = gtk_button_new_from_stock ("gtk-close");
	gtk_widget_show (button_close);
	g_signal_connect (G_OBJECT (button_close), "clicked",
							G_CALLBACK (servlist_close_cb), 0);
	gtk_container_add (GTK_CONTAINER (hbuttonbox1), button_close);
	gtk_widget_set_can_default (button_close, TRUE);

	button_connect = gtkutil_button (hbuttonbox1, GTK_STOCK_CONNECT, NULL,
												servlist_connect_cb, NULL, _("C_onnect"));
	gtk_widget_set_can_default (button_connect, TRUE);

	g_signal_connect (G_OBJECT (entry_guser), "changed", 
					G_CALLBACK(servlist_username_changed_cb), button_connect);
	g_signal_connect (G_OBJECT (entry_nick1), "changed",
					G_CALLBACK(servlist_nick_changed_cb), button_connect);
	g_signal_connect (G_OBJECT (entry_nick2), "changed",
					G_CALLBACK(servlist_nick_changed_cb), button_connect);

	// Run validity checks now 
	servlist_nick_changed_cb (GTK_ENTRY(entry_nick2), button_connect);
	servlist_username_changed_cb (GTK_ENTRY(entry_guser), button_connect);

	gtk_label_set_mnemonic_widget (GTK_LABEL (label3), entry1);
	gtk_label_set_mnemonic_widget (GTK_LABEL (label6), entry4);
	// gtk_label_set_mnemonic_widget (GTK_LABEL (label7), entry5);

	gtk_widget_grab_focus (networks_tree);
	gtk_widget_grab_default (button_close);
*/
    gtk_widget_show_all(servlist);
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);

    gtk_main();
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);

    // Finish the activity and makes sure it is properly unloaded
    gtk_android_exit(state);
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
}

