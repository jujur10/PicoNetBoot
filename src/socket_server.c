/*
** Julien ROIRON, 2023
** socket_server.c
** File description:
** Functions which initializes and use the server socket.
*/
#include "style/common_macros.h"
#include "style/pointer.h"
#include "pico_net_boot.h"

/// @brief Function which initializes the receive function.
///
/// @see tcp_recv_fn
err_t server_receive_callback(UNUSED void PTR arg,
    struct tcp_pcb PTR tpcb, struct pbuf PTR p, err_t err)
{
    if (err == ERR_OK && p != NULL && p->len != 0 && tpcb != NULL) {
        execute_instruction(tpcb, p->payload);
        tcp_output(tpcb);
    } else if (tpcb != NULL) {
        tcp_close(tpcb);
    }
    if (p != NULL)
        pbuf_free(p);
    return err;
}

/// @brief Function which initializes the error function.
///
/// @see tcp_err_fn
void server_error_callback(void PTR arg, UNUSED err_t err)
{
    struct tcp_pcb *tpcb = (struct tcp_pcb *)arg;

    tcp_close(tpcb);
}

/// @brief Function which initializes the accept function.
///
/// @see tcp_accept_fn
err_t server_accept_callback(UNUSED void PTR arg,
    struct tcp_pcb PTR newpcb, err_t err)
{
    tcp_recv(newpcb, server_receive_callback);
    tcp_err(newpcb, server_error_callback);
    return err;
}

/// @brief Function used to initialize the server's socket and bind receive
/// function.
///
/// @return The tcp pcb pointer on success, NULL on failure.
struct tcp_pcb PTR init_socket_connection(void)
{
    struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_V4);

    if (pcb == NULL) {
        printf("Error during socket initialization.\n");
        return NULL;
    }
    if (tcp_bind(pcb, IP4_ADDR_ANY, (u16_t)atoi(SOCKET_PORT)) != ERR_OK) {
        printf("Bind error.\n");
        return NULL;
    }
    pcb = tcp_listen_with_backlog(pcb, 5);
    if (pcb == NULL) {
        printf("Listen error.\n");
        return NULL;
    }
    tcp_accept(pcb, server_accept_callback);
    return pcb;
}

void run_socket_server(void)
{
    struct tcp_pcb const *pcb = init_socket_connection();

    if (pcb == NULL)
        return;
    while (1)
        cyw43_arch_poll();
}
