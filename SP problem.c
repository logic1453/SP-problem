#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pair {
    int first;
    int second;
    int sum;
    int product;
}Pair;
int QUS_MAX=99;
int QUS_MIN=2;
int main() {
    //初始化，最初的表存在list里
    int size=(QUS_MAX-QUS_MIN+2)*(QUS_MAX-QUS_MIN+1)/2;
    Pair* list=(Pair*)malloc(size*sizeof(Pair));
    int index=0;
    for(int i=QUS_MIN;i<=QUS_MAX;i++) {
        for(int j=i;j<=QUS_MAX;j++) {
            list[index].first=i;
            list[index].second=j;
            list[index].sum=i+j;
            list[index].product=i*j;
            index++;
        }
    }

    bool *is_valid=(bool*)malloc(size*sizeof(bool));
    memset(is_valid,0,size);

    //需满足“ S: 我知道你不知道m和n, 但我也不知道”,即答案的sum可以有多种分解，且每种分解的乘积也应该有多种分解
    //找到满足上述条件的pair(is_valid设为1)
    for(int i=0;i<size;i++) {
        Pair *same_sum_list=(Pair*)malloc(size*sizeof(Pair));
        int index_of_same_sum_list=0;
        for(int j=0;j<size;j++) {
            if(list[i].sum==list[j].sum&&is_valid[j]==0&&is_valid[i]==0) {
                same_sum_list[index_of_same_sum_list++]=list[j];
            }
        }
        if(index_of_same_sum_list>1) {
            for(int k=0;k<index_of_same_sum_list;k++) {
                for(int l=0;l<size;l++) {
                    if(same_sum_list[k].product==list[l].product&&same_sum_list[k].first!=list[l].first) {
                        goto yes;
                    }
                }
                goto no;
                yes:
            }

            for(int k=0;k<index_of_same_sum_list;k++) {
                for(int l=0;l<size;l++) {
                    if(same_sum_list[k].first==list[l].first&&same_sum_list[k].second==list[l].second) {
                        is_valid[l]=1;
                        break;
                    }
                }

            }

        }
        no:
        free(same_sum_list);
    }

    //需满足“ P: 现在我知道了! ”，即答案的product对应的各种分解在去除后的list中应只出现一次
    //去除不满足上述条件的pair(is_valid设为0)
    int product_max=QUS_MAX*QUS_MAX;
    int *product_count=(int*)malloc((product_max+1)*sizeof(int));
    memset(product_count,0,product_max+1);
    for(int i=0;i<size;i++) {
        if(!is_valid[i])continue;
        for(int j=0;j<size;j++) {
            if(is_valid[j]&&list[j].product==list[i].product) {
                product_count[list[i].product]++;
            }
        }
    }
    for(int i=0;i<size;i++) {
        if(is_valid[i]==1&&product_count[list[i].product]!=1) {
            is_valid[i]=0;
        }
    }
    free(product_count);
    //需满足“ S: 现在我也知道了!”，即答案的sum对应的各种分解在去除后的list中应只出现一次
    //去除不满足上述条件的pair(is_valid设为0)
    int sum_max=QUS_MAX+QUS_MAX;
    int *sum_count=(int*)malloc((sum_max+1)*sizeof(int));
    memset(sum_count,0,sum_max+1);
    for(int i=0;i<size;i++) {
        if(!is_valid[i])continue;
        for(int j=0;j<size;j++) {
            if(is_valid[j]&&list[j].sum==list[i].sum) {
                sum_count[list[i].sum]++;
            }
        }
    }
    for(int i=0;i<size;i++) {
        if(is_valid[i]==1&&sum_count[list[i].sum]!=1) {
            is_valid[i]=0;
        }
    }
    free(sum_count);
    //打印满足条件的pair
    for(int i=0;i<size;i++) {
        if(is_valid[i]) {
            printf("m=%d n=%d\n",list[i].first,list[i].second);
        }
    }
    //free
    free(is_valid);
    free(list);
}