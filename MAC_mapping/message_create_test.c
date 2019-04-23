#include "mac_mapping.h"

int main(int argc, char* argv[]) {
  int msg_len;
  int buf_len;
  if (argc > 1) {
    buf_len = atoi(argv[1]);
    msg_len = buf_len - 1;
  } else {
    puts("If you run ./message_create_test [n], this test code will run with an n-byte buffer.\n");
    msg_len = 80;
    buf_len = 81;
  }
  printf("Max message length is %d, buffer length is %d\n", msg_len, buf_len);
  char buffer[buf_len];
  create_message(buffer, buf_len);
  puts(buffer);
}
