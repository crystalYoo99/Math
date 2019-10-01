#include <stdio.h>

int main ()
{
        FILE * f = fopen("origin_sudoku", "r");
    FILE * fp = fopen("formula", "w") ;

        int x, y;
    char input[9][9];
    int star_addr[9];
    int num[81];
    int num_addr[81];
    int count_num=0;
    int count_star=0;

    //원본 파일에서 줄로 읽어오기
    for (int i = 0; i<9; i++){
        fscanf(f, "%s", input[i]);
        printf("%s\n",input[i]);
        }
    //변수 만들기
        for (y = 1 ; y <= 9 ; y++)
                for (x = 1 ; x <= 9 ; x++)
                        fprintf(fp, "(declare-const a%d%d Int)\n", y, x) ;

    //월본에서 별과 숫자 위치 저장
    for(y=0; y<9; y++) {
        for(x=0; x<9; x++) {
            if(input[x][y]=='*') {
                star_addr[count_star] = (x+1)*10+(y+1);
                count_star++;
            }
            else if(input[x][y] == '?') {}
            else {
                num[count_num] = input[x][y]-'0';
                num_addr[count_num] = (x+1)*10 +y+1;
                count_num++;
            }
        }
    }
    num[count_num] = '\0';
    num_addr[count_num] = '\0';
    star_addr[count_star] = '\0';

        //한 칸은 1이상 9이하
        for(y=1; y<=9; y++)
                for(x=1; x<=9; x++)
                        fprintf(fp, "(assert (and (<= a%d%d 9) (<= 1 a%d%d)))\n", y, x, y, x);
    //숫자 초기화
    for(int i = 0; i < count_num; i++) {
    fprintf(fp, "(assert (= a%d%d %d ))\n", num_addr[i]/10, num_addr[i]%10, num[i]);}

//한 행 다 달라야 한다
        for (x = 1 ; x <= 9 ; x++) {
                fprintf(fp, "(assert (distinct");
        for(y = 1; y <= 9; y++) {
                fprintf(fp, " a%d%d", y, x);
        }
                fprintf(fp, "))\n");
        }


    //한 열 다 달라야 한다
        for (y = 1 ; y <= 9 ; y++) {
                fprintf(fp, "(assert (distinct");
                for( x = 1; x<= 9; x++) {
                        fprintf(fp, " a%d%d", y, x);
        }
                fprintf(fp, "))\n");
        }

    //한 박스 다 달라야 한다
    for(int s = 0; s <= 2; s++) {
        for(int r = 0; r <= 2; r++) {
                fprintf(fp, "(assert (distinct");
            for(y = 1; y<=3; y++) {
                for(x = 1; x <= 3; x++) {
                        fprintf(fp, " a%d%d", 3*s+y, 3*r+x);
                }
            }
        fprintf(fp, "))\n");
        }
    }
    fprintf(fp,"\n");
    //별끼리 달라야함
        fprintf(fp, "(assert (distinct");
    for(int i = 0; i < count_star; i++) {
            fprintf(fp, " a%d%d", star_addr[i]/10, star_addr[i]%10);
    }
        fprintf(fp, "))\n");


        fprintf(fp, "(check-sat)\n(get-model)\n") ;

        fclose(fp) ;

       /* FILE * fin = popen("z3 formula", "r") ; //FIXME
        char buf[128] ;
        fscanf(fin, "%s %s", buf, buf) ;
        while (!feof(fin)) {
                fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
                fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
                fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
                fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
                fscanf(fin, "%s", buf) ; printf("%s\n", buf) ;
        }
        pclose(fin) ;
}*/
FILE * fin = popen("z3 formula", "r") ; //FIXME
        int i, j, k;
        char board[10][10];
        char b[128] ;
        char s[128];
        char t[128];
        fscanf(fin, "%s %s", b, b) ;
        for(k =0; k < 81; k++) {
                fscanf(fin, "%s %s %s %s %s", b, s, b, b, t);
                i = s[1] - '0';
                j = s[2] - '0';

                board[i][j] = t[0] - '0';
        }
        for(i = 1; i <= 9; i++) {
                for(j = 1; j <= 9; j++) {
                        printf("%d ", board[i][j]);
                }
                printf("\n");

        
}
        pclose(fin) ;
}
