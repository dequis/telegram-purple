#include <sys/types.h>
#include "mtproto-common.h"
#include "telegram.h"
#include "msglog.h"

/* 
 * Events
 */

/*
 * New message received
 */
void (*on_msg_handler)(struct message *M);
void on_update_new_message(void (*on_msg)(struct message *M)) {
  on_msg_handler = on_msg;
}
void event_update_new_message(struct message *M) {
  if (on_msg_handler) {
    on_msg_handler(M);
  }
}

/*
 * User allocated
 */
void (*on_user_allocated_handler)(peer_t *user);
void on_user_allocated(void (*handler)(peer_t *user)) {
  on_user_allocated_handler = handler;
}
void event_user_allocated(peer_t *user) {
  if (on_user_allocated_handler) {
    on_user_allocated_handler(user);
  }
}

/*
 * Chat allocated
 */
void (*on_chat_allocated_handler)(peer_t *chat);
void on_chat_allocated(void (*handler)(peer_t *chat)) 
{
  on_chat_allocated_handler = handler;
}
void event_chat_allocated(peer_t *chat) 
{
  if (on_chat_allocated_handler) {
    on_chat_allocated_handler(chat);
  }
}

/*
 * Callback to create proxy connections
 */
void (*proxy_connection_source)(const char *host, int port, void (*on_connection_created)(int fd)) = NULL;
void *proxy_connection_data = NULL;
void set_proxy_connection_source (void (*connection_source)(const char *host, int port, 
    void (*on_connection_created)(int fd)), void* data) 
{
    proxy_connection_source = connection_source;
    proxy_connection_data = data;
}

// template
//void (*on_blarg_handler)(type);
//void on_blarg(void (*handler)(type)) 
//{
//  on_blarg_handler = handler;
//}
//void event_blarg(type) 
//{
//  if (on_blarg_handler) 
//  {
//    on_blarg_handler(type);
//  }
//}