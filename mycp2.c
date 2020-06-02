#include <stdio.h>                 // perror のため
#include <stdlib.h>                // exit のため
#include <fcntl.h>                 // open のため
#include <unistd.h>                // read,write,close のため
#define  BSIZ 1000                 // バッファサイズ

int main(int argc, char *argv[]) {
  int fd1;                         // コピー元用のFD
  int fd2;                         // コピー先用のFD
  ssize_t len;                     // 実際に読んだバイト数
  char buf[BSIZ];                  // バッファ

  // 以下にプログラムを書き加えて完成させる．
  //
  // ヒント：書き込みopenは次のようにすると良い．
  // fd2 = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, 0644);

  close(fd1);
  close(fd2);
  return 0;                        // 正常終了
}
