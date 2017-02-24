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
#include <Provider.h>
#include <android_native_app_glue.h>
#include <android/log.h>
#include <gtkandroid.h>
#include <pthread.h>//线程
#include <unistd.h>
#include <robot_main.h>
#include <log_print.h>
//#include <hexchat.h>




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

typedef struct ircnet
{
	char *name;
	char *nick;
	char *nick2;
	char *user;
	char *real;
	char *pass;
	int logintype;
	char *encoding;
	GSList *servlist;
	GSList *commandlist;
	GSList *favchanlist;
	int selected;
	guint32 flags;
} ircnet;

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

char *geTime = NULL;
jclass myClass;
extern JNIEnv* jniEnv;



static void
servlist_sort (GtkWidget *button, gpointer none)
{
	/*network_list=g_slist_sort(network_list,(GCompareFunc)servlist_compare);
	servlist_networks_populate (networks_tree, network_list);*/
}

static void
servlist_edit_cb (GtkWidget *but, gpointer none)
{
	__android_log_print(10,"ouyang","---EDIT--------------------------------%s---%d-----------------------------------------------------------------------",__FILE__,__LINE__);
	pthread_t thread_1,thread_2;
	//pthread_create(&thread_1,NULL,main,NULL);
	main();
	//GetTime();
	/*if (!servlist_has_selection (GTK_TREE_VIEW (networks_tree)))
		return;

	edit_win = servlist_open_edit (serverlist_win, selected_net);
	gtkutil_set_icon (edit_win);
	servlist_servers_populate (selected_net, edit_trees[SERVER_TREE]);
	servlist_channels_populate (selected_net, edit_trees[CHANNEL_TREE]);
	servlist_commands_populate (selected_net, edit_trees[CMD_TREE]);
	g_signal_connect (G_OBJECT (edit_win), "delete_event",
						 	G_CALLBACK (servlist_editwin_delete_cb), 0);
	g_signal_connect (G_OBJECT (edit_win), "configure_event",
							G_CALLBACK (servlist_edit_configure_cb), 0);
	gtk_widget_show (edit_win);*/
}

static void
servlist_favor (GtkWidget *button, gpointer none)
{
	/*GtkTreeSelection *sel;
	GtkTreeModel *model;
	GtkTreeIter iter;

	if (!selected_net)
		return;

	sel = gtk_tree_view_get_selection (GTK_TREE_VIEW (networks_tree));
	if (gtk_tree_selection_get_selected (sel, &model, &iter))
	{
		if (selected_net->flags & FLAG_FAVORITE)
		{
			gtk_list_store_set (GTK_LIST_STORE (model), &iter, 2, 400, -1);
			selected_net->flags &= ~FLAG_FAVORITE;
		}
		else
		{
			gtk_list_store_set (GTK_LIST_STORE (model), &iter, 2, 800, -1);
			selected_net->flags |= FLAG_FAVORITE;
		}
	}*/
}

static void
servlist_celledit_cb (GtkCellRendererText *cell, gchar *arg1, gchar *arg2,
							 gpointer user_data)
{
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
	/*GtkTreeModel *model = (GtkTreeModel *)user_data;
	GtkTreeIter iter;
	GtkTreePath *path;
	char *netname;
	ircnet *net;

	if (!arg1 || !arg2)
		return;

	path = gtk_tree_path_new_from_string (arg1);
	if (!path)
		return;

	if (!gtk_tree_model_get_iter (model, &iter, path))
	{
		gtk_tree_path_free (path);
		return;
	}
	gtk_tree_model_get (model, &iter, 0, &netname, -1);

	net = servlist_net_find (netname, NULL, strcmp);
	g_free (netname);
	if (net)
	{
		// delete empty item 
		if (arg2[0] == 0)
		{
			servlist_deletenetwork (net);
			gtk_tree_path_free (path);
			return;
		}

		netname = net->name;
		net->name = g_strdup (arg2);
		gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, net->name, -1);
		g_free (netname);
	}

	gtk_tree_path_free (path);*/
}

static void
servlist_addnet_cb (GtkWidget *item, GtkTreeView *treeview)
{
	
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
	/*GtkTreeIter iter;
	GtkListStore *store;
	ircnet *net;

	net = servlist_net_add (_("New Network"), "", TRUE);
	net->encoding = g_strdup (IRC_DEFAULT_CHARSET);
	servlist_server_add (net, "newserver/6667");

	store = (GtkListStore *)gtk_tree_view_get_model (treeview);
	gtk_list_store_prepend (store, &iter);
	gtk_list_store_set (store, &iter, 0, net->name, 1, 1, -1);

	// select this network
	servlist_select_and_show (GTK_TREE_VIEW (networks_tree), &iter, store);
	servlist_start_editing (GTK_TREE_VIEW (networks_tree));

	servlist_network_row_cb (gtk_tree_view_get_selection (GTK_TREE_VIEW (networks_tree)), NULL);*/
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
}



static void
no_servlist (GtkWidget * igad, gpointer serv)
{
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
	/*if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (igad)))
		prefs.hex_gui_slist_skip = TRUE;
	else
		prefs.hex_gui_slist_skip = FALSE;*/
}

static void
fav_servlist (GtkWidget * igad, gpointer serv)
{
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
	/*if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (igad)))
		prefs.hex_gui_slist_fav = TRUE;
	else
		prefs.hex_gui_slist_fav = FALSE;

	servlist_networks_populate (networks_tree, network_list);
	*/
}

static void
servlist_deletenet_cb (GtkWidget *item, ircnet *net)
{
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
	/*GtkWidget *dialog;

	if (!servlist_has_selection (GTK_TREE_VIEW (networks_tree)))
		return;

	net = selected_net;
	if (!net)
		return;
	dialog = gtk_message_dialog_new (GTK_WINDOW (serverlist_win),
												GTK_DIALOG_DESTROY_WITH_PARENT |
												GTK_DIALOG_MODAL,
												GTK_MESSAGE_QUESTION,
												GTK_BUTTONS_OK_CANCEL,
							_("Really remove network \"%s\" and all its servers?"),
												net->name);
	g_signal_connect (dialog, "response",
							G_CALLBACK (servlist_deletenetdialog_cb), net);
	gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_MOUSE);
	gtk_widget_show (dialog);*/
	
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
	gtk_android_init(state);
    //g_usleep(3 * 1000000);
    /*if(init_get_env(state) != 0)
    {
    	__android_log_print(10,"ouyang","-----%s---%d---%s-----",__FILE__,__LINE__,"getEnv is error,exit!!!");
    	exit(0);
    }*/
    __android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
    //getWebPicture(state);
    /*
    struct android_app *app = state;
    jobject activityInstance = app->activity->clazz;
    JavaVM* jvm = app->activity->vm;
    JNIEnv *env = NULL;

    (*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);

    if ((*jvm)->AttachCurrentThread(jvm, &env, NULL) < 0)
    {
     LOGE("callback_handler: failed to attach current thread");
     return;
    }

    jclass clazz = (*env)->GetObjectClass(env, activityInstance);
    if (!clazz) {
    LOGE("callback_handler: failed to get WebPicCls class reference");

    (*jvm)->DetachCurrentThread(app->activity->vm);
    return;
    }

    jmethodID methodID = (*env)->GetMethodID(env, clazz, "LoadWebSite", "(Ljava/lang/String;)V");
    if (!methodID) {
    LOGE("callback_handler: failed to get LoadWebSite method ID");
    (*jvm)->DetachCurrentThread(app->activity->vm);
    return;
    }

    jstring url= (*env)->NewStringUTF(env, "http://198.168.1.104");

    (*env)->CallVoidMethod(env, activityInstance, methodID, url);

    (*env)->ReleaseStringUTFChars(env,url,(*env)->GetStringUTFChars(env, url, 0));

    (*jvm)->DetachCurrentThread(jvm);
    
    */
    
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);

    servlist = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width (GTK_CONTAINER (servlist), 4);
	gtk_window_set_title (GTK_WINDOW (servlist), ("DISPLAY_NAME: Network List"));
	gtk_window_set_default_size (GTK_WINDOW (servlist), 2,20);
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
	
	geTime = GetTime();
	entry_nick1 = entry1 = gtk_entry_new ();
	__android_log_print(10,"ouyang","-----%s---%d-----",geTime,__LINE__);
	gtk_entry_set_text (GTK_ENTRY (entry1), geTime);//输入框文本
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
		gtk_check_button_new_with_mnemonic (("Skip network list on startup"));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton_skip),
											"prefs.hex_gui_slist_skip");
	gtk_container_add (GTK_CONTAINER (hbox), checkbutton_skip);
	g_signal_connect (G_OBJECT (checkbutton_skip), "toggled",
							G_CALLBACK (no_servlist), 0);
	gtk_widget_show (checkbutton_skip);

	checkbutton_fav =
		gtk_check_button_new_with_mnemonic (("Show favorites only"));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton_fav),
											"prefs.hex_gui_slist_fav");
	gtk_container_add (GTK_CONTAINER (hbox), checkbutton_fav);
	g_signal_connect (G_OBJECT (checkbutton_fav), "toggled",
							G_CALLBACK (fav_servlist), 0);
	gtk_widget_show (checkbutton_fav);//TURE

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

	button_edit = gtk_button_new_with_mnemonic (("_Edit..."));
	g_signal_connect (G_OBJECT (button_edit), "clicked",
							G_CALLBACK (servlist_edit_cb), 0);
	gtk_widget_show (button_edit);
	gtk_container_add (GTK_CONTAINER (vbuttonbox2), button_edit);
	gtk_widget_set_can_default (button_edit, TRUE);

	button_sort = gtk_button_new_with_mnemonic (("_Sort"));
	gtk_widget_set_tooltip_text (button_sort, ("Sorts the network list in alphabetical order. "
				"Use SHIFT-UP and SHIFT-DOWN keys to move a row."));
	g_signal_connect (G_OBJECT (button_sort), "clicked",
							G_CALLBACK (servlist_sort), 0);
	gtk_widget_show (button_sort);
	gtk_container_add (GTK_CONTAINER (vbuttonbox2), button_sort);
	gtk_widget_set_can_default (button_sort, TRUE);

	button_sort = gtk_button_new_with_mnemonic (("_Favor"));
	gtk_widget_set_tooltip_text (button_sort, ("Mark or unmark this network as a favorite."));
	g_signal_connect (G_OBJECT (button_sort), "clicked",
							G_CALLBACK (servlist_favor), 0);
	gtk_widget_show (button_sort);
	gtk_container_add (GTK_CONTAINER (vbuttonbox2), button_sort);
	gtk_widget_set_can_default (button_sort, TRUE);

	hseparator1 = gtk_hseparator_new ();
	gtk_widget_show (hseparator1);
	gtk_box_pack_start (GTK_BOX (vbox1), hseparator1, FALSE, TRUE, 4);
	
/*
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

