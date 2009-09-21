#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(void) {

  /* Наши ID процесса и сессии */
  pid_t pid, sid;

  /* Ответвляемся от родительского процесса */
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  /* Если с PID'ом все получилось, то родительский процесс можно завершить. */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  /* Изменяем файловую маску */
  umask(0);

  /* Здесь можно открывать любые журналы */        

  /* Создание нового SID для дочернего процесса */
  sid = setsid();
  if (sid < 0) {
    /* Журналируем любой сбой */
    exit(EXIT_FAILURE);
  }

  /* Изменяем текущий рабочий каталог */
  if ((chdir("/")) < 0) {
    /* Журналируем любой сбой */
    exit(EXIT_FAILURE);
  }

  /* Закрываем стандартные файловые дескрипторы */
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  /* Специфичная для демона инициализация проходит тут */

  /* Большой Цикл */
  while (1) {
	/* Делаем здесь чего-нибудь ... */
	sleep(30); /* ждем 30 секунд */
  }
  exit(EXIT_SUCCESS);
}
