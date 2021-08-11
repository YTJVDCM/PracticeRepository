/* main.c
 * Git practice (RPG battle)
 *
 * How to compile
 * gcc -Wall -o main main.c
 *
 * Code written by YTJVDCM
 *
 *
 * This code licensed by MIT License
 *  https://opensource.org/licenses/MIT
 * Japanese
 *  https://licenses.opensource.jp/MIT/MIT.html
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#define MONSTER_COUNT 5
#define DEFAULT_HP 1000
#define DEFAULT_ATK 10

void input(char *in); //INT_MAX文字までの文字を入力できる関数

struct _MONSTER {
    char *name; //名前
    int hp; //HP
    int atk; //攻撃力
    int canescape; //逃げやすさ(0-100,0で逃げれない)
}typedef monster;

void attack(char *name,int atk,monster *monster_data);//攻撃する

void damage(char *name,int *hp,monster *monster_data);//攻撃される

bool escape(monster monster_data);//逃げられるかの判定

int main(){
    srand(time(NULL));
    bool turnflag = false;
    bool escapeflag = false;
    int choosed_id;
    int choose;

    char *name;
    int hp=DEFAULT_HP;//プレイヤーのHP(defineで定義)
    int atk=DEFAULT_ATK;//プレイヤーの攻撃力(defineで定義)

    //モンスターの各種パラメーター
    char *monsters_name[]={"スライム","ゾンビ","ドラゴン","老害","魔王"};
    int monsters_hp[]={20,50,100,1000,1000};
    int monsters_atk[]={10,20,100,1000,1000};
    int monsters_canescape[]={100,90,0,0,0};

    //メモリ取得
    name = (char *)malloc(sizeof(char));

    printf("名前を入力 > ");
    input(name);

    choosed_id = rand() % MONSTER_COUNT;
    monster choosed_monster={monsters_name[choosed_id],monsters_hp[choosed_id],monsters_atk[choosed_id],monsters_canescape[choosed_id]};
    
    printf("%s があらわれた!\n",choosed_monster.name);
    while(1){
        while(1){
            fflush(stdin); //入力バッファ削除(安全策)
            turnflag = false;
            printf("%s の残りHP : %d\n",name,hp);
            printf("%s はどうする\n",name);
            printf("0.たたかう\t1.まほう\t2.どうぐ\t3.にげる\n");
            scanf("%d",&choose);
            switch(choose){
                case 0:
                    attack(name,atk,&choosed_monster);
                    turnflag = true;
                    break;
                case 1:
                    printf("この機能は、まだ実装されていない!!\n");
                    usleep(700000);
                    break;
                case 2:
                    printf("この機能は、まだ実装されていない!!\n");
                    usleep(700000);
                    break;
                case 3:
                    printf("%s は逃げようとした!\n",name);
                    usleep(700000);
                    if(escape(choosed_monster) == true){
                        printf("逃げるのに成功した!\n");
                        escapeflag = true;
                    }else{
                        printf("しかし、逃げられなかった!\n");
                    }
                    turnflag = true;
                    usleep(700000);
                    break;
                default:
                    printf("不正な値です。\n");
            }
            if(turnflag == true)break;
        }
        if(escapeflag == true)break;
        if(choosed_monster.hp<=0){
            printf("%s に勝利した!\n",choosed_monster.name);
            break;
        }
        damage(name,&hp,&choosed_monster);
        if(hp<=0){
            printf("%s に敗北してしまった...\n",choosed_monster.name);
            break;
        }
    }

    usleep(700000);
    printf("GAME OVER\n");

    free(name);

    return 0;
}

void input(char *in){
    char *tmp,ic;

    //ここ環境によっては動かないかもしれない
    for(int i=1;;i++){
        scanf("%c",&ic);
        if(ic == '\n')break;
        
        tmp = (char*)realloc(in,(sizeof(char)*i)+1);
        if(tmp == NULL){
            printf("An error occurred\n");
            exit(1);
        }
        
        in = tmp;
        in[i]=0;
        in[i-1]=ic;
    }
}

void attack(char *name,int atk,monster *monster_data){
    srand(time(NULL));
    int damage;

    printf("%s の攻撃\n",name);
    damage = atk + (rand() % ((atk/10)+1));
    monster_data->hp -= damage;

    usleep(700000);
    printf("%sに%dのダメージ!\n",monster_data->name,damage);
    usleep(700000);
}

void damage(char *name,int *hp,monster *monster_data){
    srand(time(NULL));
    int damage;

    printf("%s の攻撃\n",monster_data->name);
    damage = monster_data->atk + (rand() % ((monster_data->atk/10)+1));
    *hp-=damage;

    usleep(700000);
    printf("%sに%dのダメージ!\n",name,damage);
    usleep(700000);
}

bool escape(monster monster_data){
    srand(time(NULL));
    int success;
    success = rand()%(100+1);
    if(success < monster_data.canescape)return true;
    
    return false;
}
