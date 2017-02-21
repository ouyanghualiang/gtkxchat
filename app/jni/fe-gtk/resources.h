#ifndef __RESOURCE_hexchat_H__
#define __RESOURCE_hexchat_H__

#include <gio/gio.h>

extern GResource *hexchat_get_resource (void);

extern void hexchat_register_resource (void);
extern void hexchat_unregister_resource (void);

#endif
