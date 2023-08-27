#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>
#include "../storage/map.h"

void get_request(void* socket, char* request) {
    zmq_msg_t request_msg;
    zmq_msg_init(&request_msg);
    zmq_msg_recv(&request_msg, socket, 0);
    memcpy(request, zmq_msg_data(&request_msg), zmq_msg_size(&request_msg));
    zmq_msg_close(&request_msg);
}

void send_reply(void* socket, char* message) {
    zmq_msg_t reply_msg;
    zmq_msg_init_size(&reply_msg, strlen(message)+1);
    memcpy(zmq_msg_data(&reply_msg), message, strlen(message)+1);
    zmq_msg_send(&reply_msg, socket, 0);
    zmq_msg_close(&reply_msg);
}

int main(int argc, char* argv[]) {
    printf("Ok: %d\n", getpid());

    int id = atoi(argv[1]);
    const int size = 50;
    HashTable* dictionary = ht_create(size);

    void* context = zmq_ctx_new();
	void* respond_socket = zmq_socket(context, ZMQ_REP);

    char adress[100];
    sprintf(adress, "tcp://*:%d", 10000 + id);
    zmq_bind(respond_socket, adress);

    for(;;) {
        char request[100];
        char reply[100];
        get_request(respond_socket, request);
        printf("Compute %d: received '%s'\n", id, request);
        if (!strcmp(request, "remove")) {
            ht_destroy(dictionary);
            printf("Compute %d: node will be destroyed\n", id);
            sprintf(reply, "Ok");
            send_reply(respond_socket, reply);
            zmq_close(respond_socket);
	        zmq_ctx_destroy(context);
            exit(0);
        } else if (!strcmp(request, "ping")) {
            if (dictionary == NULL) {
                printf("Compute %d: node hasn't a local dictionary\n", id);
                sprintf(reply, "Ok: 0");
            } else {
                printf("Compute %d: node has a local dictionary\n", id);
                sprintf(reply, "Ok: 1");
            }
        } else if (!strcmp(request, "print")) {
            printf("Compute %d: the current content of the dictionary:\n", id);
            ht_print(dictionary);
            sprintf(reply, "Ok:%d", id);
        } else {
            char* command = strtok(request, " ");
            char* key = strtok(NULL, " ");
            if (!strcmp(command, "save")) {
                int value = atoi(strtok(NULL, " "));
                ht_insert(dictionary, key, value);
                printf("Compute %d: key '%s' was saved with value '%d'\n", id, key, value);
                sprintf(reply, "Ok: %d", id);
            } else if (!strcmp(command, "return")) {
                Node* save_node = ht_search(dictionary, key);
                if (save_node == NULL) {
                    printf("Compute %d: this key not in map\n", id);
                    sprintf(reply, "OK:%d:'%s' not found", id, key);
                } else {
                    printf("Compute %d: value is %d\n", id, save_node->value);
                    sprintf(reply, "Ok:%d:%d", id, save_node->value);
                }
            }
        }
        send_reply(respond_socket, reply);
    }
}