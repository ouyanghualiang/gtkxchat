
#ifndef ___hexchat_marshal_MARSHAL_H__
#define ___hexchat_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* VOID:OBJECT,OBJECT (marshalers.list:2) */
extern void _hexchat_marshal_VOID__OBJECT_OBJECT (GClosure     *closure,
                                                  GValue       *return_value,
                                                  guint         n_param_values,
                                                  const GValue *param_values,
                                                  gpointer      invocation_hint,
                                                  gpointer      marshal_data);

/* VOID:POINTER,POINTER (marshalers.list:3) */
extern void _hexchat_marshal_VOID__POINTER_POINTER (GClosure     *closure,
                                                    GValue       *return_value,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint,
                                                    gpointer      marshal_data);

/* BOOLEAN:STRING (marshalers.list:5) */
extern void _hexchat_marshal_BOOLEAN__STRING (GClosure     *closure,
                                              GValue       *return_value,
                                              guint         n_param_values,
                                              const GValue *param_values,
                                              gpointer      invocation_hint,
                                              gpointer      marshal_data);

/* OBJECT:OBJECT,OBJECT (marshalers.list:6) */
extern void _hexchat_marshal_OBJECT__OBJECT_OBJECT (GClosure     *closure,
                                                    GValue       *return_value,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint,
                                                    gpointer      marshal_data);

/* VOID:POINTER,POINTER,UINT,UINT (marshalers.list:8) */
extern void _hexchat_marshal_VOID__POINTER_POINTER_UINT_UINT (GClosure     *closure,
                                                              GValue       *return_value,
                                                              guint         n_param_values,
                                                              const GValue *param_values,
                                                              gpointer      invocation_hint,
                                                              gpointer      marshal_data);

G_END_DECLS

#endif /* ___hexchat_marshal_MARSHAL_H__ */

