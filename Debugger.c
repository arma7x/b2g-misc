#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
	int fd;
	struct sockaddr_un addr;
	int ok = 1;
	int len;

	if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		ok = 0;
	}

	if (ok) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, "/data/local/debugger-socket");
		if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
			perror("connect");
			ok = 0;
		}
	}

	if (ok) {
		char buff[20480];
		if ((len = recv(fd, buff, 20480, 0)) < 0) {
			perror("recv");
			ok = 0;
		}
		printf ("\nConncted receive %d %s\n", len, buff);
	}

	if (ok) {
		char buff[20480];
		strcpy (buff, "31:{\"to\":\"root\",\"type\":\"listTabs\"}");
		if (send(fd, buff, strlen(buff)+1, 0) == -1) {
			perror("\n1 send");
			ok = 0;
		}
		printf ("\n1 sent %s\n", buff);
	}

	if (ok) {
		char buff[20480];
		if ((len = recv(fd, buff, 20480, 0)) < 0) {
			perror("recv");
			ok = 0;
		}
		printf ("\nreceive %d %s\n", len, buff);
		int length;
		char json[20480];
		sscanf(buff, "%d:%s", &length, json);
		printf("\n%s\n", json);
	}

	if (fd >= 0) {
		close(fd);
	}

	return 0;
}
