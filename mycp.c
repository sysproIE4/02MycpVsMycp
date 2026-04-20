#include <stdio.h>  // fopen, fprintf, perror, fgetc, fputc などのため

int main(int argc, char *argv[]) {
  FILE *fps;                                          // コピー元ファイル用
  FILE *fpd;                                          // コピー先ファイル用
  int  ch;                                            // コピー時に使用

  if (argc != 3) {                                    // 引数の数が予定と異なる
    fprintf(stderr,                                   // 標準エラー出力に
            "Usage: %s srcfile destfile\n", argv[0]); //  使用方法を表示して
    return 1;                                         //  エラー終了
  }

  if ((fps = fopen(argv[1], "rb")) == NULL) {         // コピー元ファイルを開く
    perror(argv[1]);                                  // エラー原因を表示
    return 1;                                         //  エラー終了
  }

  if ((fpd = fopen(argv[2], "wb")) == NULL) {         // コピー先ファイルを開く
    perror(argv[2]);                                  // エラー原因を表示
    return 1;                                         //  エラー終了
  }

  while ((ch=getc(fps)) != EOF) {                     // EOF になるまで
    putc(ch, fpd);                                    //  1バイト毎にコピーする
  }

  fclose(fps);                                        // ファイルを閉じる
  fclose(fpd);

  return 0;                                          // 正常終了
}
