#include <stdio.h>                             // 入出力のために必要
#include <stdlib.h>                            // exit のために必要

// err_exit : ファイルのオープンに失敗したときエラーメッセージを表示し終了
void err_exit(char *prog, char *fname) {
  fprintf(stderr, "%s : can't open %s\n",      // 標準エラー出力に
          prog, fname);                        // エラーメッセージを表示し
  exit(1);                                     // エラー終了
}

int main(int argc, char *argv[]) {
  FILE *fps;                                   // コピー元ファイル用
  FILE *fpd;                                   // コピー先ファイル用
  int  ch;                                     // コピー時使用

  if (argc != 4) {                             // 引数の個数が予定と異なる
    fprintf(stderr,                            // 標準エラー出力に
            "Usage: %s <srcfile> <dstfile> <BSIZ>\n", // 使用方法を表示して
            argv[0]);
    exit(1);                                   // エラー終了
  }

  int bsiz = atoi(argv[3]);
//  printf("bsiz=%d\n", bsiz);
  if (bsiz==0) {
    fprintf(stderr, "error BSIZ=0\n");
    exit(1);
  }

  if ((fps = fopen(argv[1], "rb"))==NULL) {    // コピー元のオープン失敗
    err_exit(argv[0], argv[1]);
  }
  char bufs[bsiz];
  if (setvbuf(fps, bufs, _IOFBF, bsiz)!=0) {
    perror("setvbuf1");
    exit(1);
  }

  if ((fpd = fopen(argv[2], "wb"))==NULL) {    // コピー先のオープン失敗
    err_exit(argv[0], argv[2]);
  }
  char bufd[bsiz];
  if (setvbuf(fpd, bufd, _IOFBF, bsiz)!=0) {
    perror("setvbuf2");
    exit(1);
  }

  while((ch=getc(fps)) != EOF) {               // EOF になるまで
    putc(ch ,fpd);                             // 1バイト毎のコピー
  }

  fclose(fps);                                 // ファイルクローズ
  fclose(fpd);

  return 0;                                    // 正常終了
}
