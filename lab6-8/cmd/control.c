#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <zmq.h>
#include "../topology/bst.h"

void print_menu() {
    printf("Menu:\n");
    printf("\t1. create <ID> -- create a compute node\n");
    printf("\t2. exec <ID> <KEY> optional <VALUE> -- if there is no value, the value by key will be obtained, otherwise the value <VALUE> will be stored by key <KEY>\n");
    printf("\t3. print <ID> -- prints the contents of the compute node dictionary\n");
    printf("\t4. ping <ID> -- checking if a local dictionary has been created on the compute node\n");
    printf("\t5. pingall -- ping command is executed for all compute nodes\n");
    printf("\t6. remove <ID> -- delete a compute node\n");
    printf("\t7. exit -- stop program\n");
}

void send_and_receive(int id, char* message, char* reply) {
    void* context = zmq_ctx_new();
    void* request_socket = zmq_socket(context, ZMQ_REQ);

    char adress[100];
    sprintf(adress, "tcp://localhost:%d", 10000 + id);
    zmq_connect(request_socket, adress);

    zmq_msg_t req_msg;
    zmq_msg_init_size(&req_msg, strlen(message) + 1);
    memcpy(zmq_msg_data(&req_msg), message, strlen(message) + 1);
    zmq_msg_send(&req_msg, request_socket, 0);
    zmq_msg_close(&req_msg);

    printf("Control: sending a message '%s' to %d\n", message, id);

    zmq_msg_t rep_msg;
    zmq_msg_init(&rep_msg);
    zmq_msg_recv(&rep_msg, request_socket, 0);
    memcpy(reply, zmq_msg_data(&rep_msg), zmq_msg_size(&rep_msg));
    zmq_msg_close(&req_msg);

    printf("Control: message from compute node '%s'\n", reply);

    zmq_close(request_socket);
    zmq_ctx_destroy(context); 
}

void remove_all_compute_nodes(Node* root) {
    if (root == NULL) {
        return;
    }
    remove_all_compute_nodes(root->left);
    remove_all_compute_nodes(root->right);
    char reply[100];
    send_and_receive(root->id, "remove", reply);
}

void pingall(Node* root, int* nodes, int* len) {
    if (root == NULL) {
        return;
    }
    pingall(root->left, nodes, len);
    char reply[100];
    send_and_receive(root->id, "ping", reply);
    char* ok = strtok(reply, " ");
    int number = atoi(strtok(NULL, " "));
    if (number) {
        nodes[*len] = root->id;
        *len += 1;
    }
    pingall(root->right, nodes, len);
}

int main() {
    int id;
    Node* root = NULL;
    print_menu();
    printf("Please enter your command:\n");
    char command[100];
    char reply[100];
    while (scanf("%s", command) != EOF) {
        if (!strcmp(command, "create")) {
            scanf("%d", &id);
            if (exist(root, id)) {
                printf("Error: id is already exist\n");
                continue;
            }    
            root = insert(root, id);

            int pid = fork();
            if (pid < 0) {
                printf("Error: Fork\n");
                exit(1);
            } 
            
            if (pid == 0) {
                char path[] = "./compute";
                char str_id[100];
                sprintf(str_id, "%d", id);
                int err = execl(path, path, str_id, NULL);
                if (err == -1) {
                    printf("Error: Execl");
                }
            }
        } else if (!strcmp(command, "remove")) {
            scanf("%d", &id);
            if (!exist(root, id)) {
                printf("Error: Not found\n");
                continue;
            }   
            root = remove_node(root, id);
            send_and_receive(id, "remove", reply);
        } else if (!strcmp(command,"exec")) {
            char key[100];
            char buffer[100];
            scanf("%d %s", &id, key);
            fgets(buffer, sizeof(char) * 100, stdin);
            buffer[strlen(buffer)-1] = '\0'; // delete '\n' 
            if (!exist(root, id)) {
                printf("Error: %d Not found\n", id);
                continue;
            }

            char message[1000];
            if (!strcmp(buffer, "")) {
                sprintf(message, "return %s", key);
            } else {
                Node* current_node = find(root, id);
                sprintf(message, "save %s%s", key, buffer);
            }
            send_and_receive(id, message, reply);
        } else if (!strcmp(command, "print")) {
            scanf("%d", &id);
            if (!exist(root, id)) {
                printf("Error: Not found\n");
                continue;
            }
            send_and_receive(id, "print", reply);
        } else if (!strcmp(command, "ping")) {
            scanf("%d", &id);
            if (!exist(root, id)) {
                printf("Error: Not found\n");
                continue;
            }
            send_and_receive(id, "ping", reply);
        } else if (!strcmp(command, "pingall")) {
            int len = 0;
            int unvailable_nodes[100];
            pingall(root, unvailable_nodes, &len);
            printf("Ok: ");
            if (len == 0) {
                printf("-1\n");
            } else {
                for (int i = 0; i < len; i++) {
                    printf("%d;", unvailable_nodes[i]);
                }
                printf("\n");
            }
        } else if (!strcmp(command,"exit")) {
            remove_all_compute_nodes(root);
            root = destroy_tree(root);
            break;
        } else {
            printf("I don't know this command. Try again.\n");
        }
    }
    return 0;
}