#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++) 
using namespace std;
typedef unsigned long long ul;
const ul hashBase=1377;
const ul hashMod =1222827239;

ul getHash(int *arr,int len){
    ul has=0; 
    // cout<<" hash: ";
    // rep(i,1,len) cout<<arr[i]<<" "; cout<<endl; 
    rep(i,1,len){
        has=(has*hashBase+arr[i])%hashMod; 
    }
    // cout<<"has"<<has<<endl;
    return has;
}
int calcAns; 
void calcComb(int *card,int sum){ // calcAns ?
    // 暂时不考虑4带2
    // static int calcAns=60; 
    if(sum>=calcAns) return; 
    rep(i,3,17){
        if(card[i]) break; 
        if(i==17){ calcAns=min(calcAns,sum); return ;}
    }
    if(card[16]&&card[17]){
        card[16]--, card[17]--; 
        calcComb(card,sum+1);
        card[16]++, card[17]++; 
        return ; 
    } // Rocket
    rep(i,3,17){
        if(card[i]==4){
            card[i]=0; calcComb(card,sum+1); card[i]=4;
        }
    } // bomb
    

    int t,cuts[20],siz,fir=0,sec=0,stk[20],top;
    rep(i,3,17) cuts[i]=0; 
    rep(i,3,14){
        if(card[i]>=2){
            t=i;
            while(card[t+1]>=2 && t<=14) t++;
            siz=t-i+1; 
            rep(j,i,t){
                cuts[j]=2, card[j]-=2; 
            }
            calcComb(card,sum+1); 
            rep(j,i,t){
                cuts[j]=0, card[j]+=2; 
            }
            i=t; 
        }
    }// sequence pair

    rep(i,3,14){ 
        if(card[i]>=1){
            t=i;
            while(card[t+1]>=1 && t<=14) t++; 
            siz=t-i+1; 
            if(siz<5){i=t; continue; }
            rep(j,i,t){ // 顺序调整
                cuts[j]++, card[j]--; 
                if(j-i+1>=5) calcComb(card,sum+1); 

            }
            rep(j,3,17) card[j]+=cuts[j], cuts[j]=0; 
            // i=t; 不优化
        }
    }// sequence
    
    rep(i,3,17){
        if(card[i]==3){
            t=i; 
            while(card[t+1]==3 && t<=14) t++; 
            siz=t-i+1; 
            rep(j,i,t){
                cuts[j]+=3, card[j]-=3; 
            }
            top=0; 
            rep(j,3,17){
                if(card[j]==1){
                    stk[++top]=j; 
                    // fir=sec, sec=i;
                    if(top==siz){
                        // if(fir==16&&sec==17) continue; // B&R
                        rep(k,1,top) card[k]--, cuts[k]++; 
                        calcComb(card,sum+1); 
                        rep(k,1,top) card[k++], cuts[k]--; 
                        break; 
                    }
                }
            }
            rep(j,3,17){
                if(card[j]==2){
                    stk[++top]=j; 
                    if(top==siz){
                        rep(k,1,top) card[k]-=2, cuts[k]+=2; 
                        calcComb(card,sum+1); 
                        rep(k,1,top) card[k]+=2, cuts[k]-=2; 
                        break; 
                    }
                }
            }
            // if(fir){ // 两个
                
            // } 
            calcComb(card,sum+1);

            rep(j,3,17) card[j]+=cuts[j], cuts[j]=0; 
            i=t; 
        }
    }
    siz=0; 
    rep(j,3,17){
        if(card[j]>=3) cout<<"Debug::"<<j<<endl; 
        if(card[j]) siz++; 
    }
    calcAns=min(calcAns,siz+sum); 
    cout<<"final"<<siz+sum<<endl;
}

struct HandCard {
    int num;
    int min_comb;
    int card[20],cards[60];
    // void calcComb(){
    //     int ans=0; 
    //     rep(i,3,17){
    //         if(card[i]==4) ans++, card[i]=0;
    //     }
    //     rep(i,3,17){
    //         if(card[i]){
    //             ; 
    //         }
    //     }
    // }
    void prints(); 
};
int fans[20]; 
class User {
  public:
    
    void readCard(); 
    void debugHand();
    void copyHand(int *arr); 
    void checkLegal(); // TODO
    void test(){
        printf("Start test:\n");
        // static int calcAns=0; 
        calcAns=60; 
        calcComb(ptrHand->card,0); 
        cout<<calcAns<<endl;
        // ptrHand->prints(); 
        printf("End test:\n");

        while(1){
            rep(i,3,17) fans[i]=0; 
            // search(xcard,ycard,last,1);
        }
        
    }
  private:
    HandCard *ptrHand; 
}Alice, Bob, Last; 

// dfsTriplet(tcard,(siz-leng*3)/leng);
int vecNum; 
// vector<int> vec[1000][20];
int vec[1000][20],dfsAns[20];  
void dfsTriplet2(int *arr,int num,int size, int idx, int now){
    if(now==num){
        ++vecNum;
        rep(i,3,17) vec[vecNum][i]=dfsAns[i]; 
        return ;
    }
    rep(i,idx,17){
        if(arr[i]>=size){
            arr[i]-=size, dfsAns[i]+=size;
            dfsTriplet2(arr,num,size,i,now+1); 
            arr[i]+=size, dfsAns[i]-=size; 
        }
    }
}

void dfsTriplet(int *arr,int num,int size){
    rep(i,1,vecNum) rep(j,3,17) vec[i][j]=0; 
    vecNum=0; 
    rep(i,3,17) dfsAns[i]=0; 
    dfsTriplet2(arr,num,size,3,0); 
    // return dfsAns; 
    // cout<<"VEC"<<vecNum<<endl;
}

map<ul,int> mp; 
int search(int *xcard,int *ycard,int *last,int isFir){
    // x是我手牌，y是对手手牌，last是对手上一轮出牌，isFir是不是第一层递归，来决定出什么
    // 1 是 我赢, 2 是我输， 有2则1，全1则2 
    // printf("------ search ------\n");
    // printf("====== search ======\n");
    // rep(i,3,17) printf("%d ",xcard[i]); cout<<endl;
    // rep(i,3,17) printf("%d ",ycard[i]); cout<<endl;
    // rep(i,3,17) printf("%d ", last[i]); cout<<endl;
    int hashArr[60];
    rep(i,1,51) hashArr[i]=0; 
    rep(i,3,17){
        hashArr[i]=xcard[i]; 
        hashArr[i+17]=ycard[i];
        hashArr[i+34]=last[i]; 
    }
    ul hashCode=getHash(hashArr,51); 
    if(mp[hashCode] && !isFir){
        // cout<<"error"<<mp[hashCode]<<endl;
        return mp[hashCode]; 
    }
    
    int first=0,siz=0,tlast[20],tcard[20],idx,sans=0,tmp,maLast,leng; 
    rep(i,3,17) siz+=ycard[i];
    if(!siz){ //cout<<"return 2"<<endl;
     mp[hashCode]=2; return 2; } 
    siz=0; 
    maLast=0;
    rep(i,3,17) tlast[i]=0;
    rep(i,3,17) siz+=last[i], maLast=max(maLast,last[i]); 
    if(!siz) first=1; 

    if(!first){ // 对手出牌了
        // 我空过
        rep(i,3,17) tlast[i]=last[i], last[i]=0;
        tmp=search(ycard,xcard,last,0); 
        rep(i,3,17) last[i]=tlast[i], tlast[i]=0;
        if(tmp==2){
            if(isFir) ;
            // cout<<"&&&&&&\n";
            mp[hashCode]=1; return 1;
        }
        if(last[16]&&last[17]){ // 对手王炸，
            mp[hashCode]=2; return 2; // 如果空过能赢，上面返回1， 否则输了，返回2
        }
        // cout<<"#$$$$$$$\n";
        if(xcard[16]&&xcard[17]){
            xcard[16]=xcard[17]=0; 
            rep(i,3,17) tlast[i]=last[i], last[i]=0; 
            last[16]=last[17]=1;
            tmp=search(ycard,xcard,last,0); 
            xcard[16]=xcard[17]=1; 
            rep(i,3,17) last[i]=tlast[i], tlast[i]=0; 
            if(tmp==2){
                if(isFir) fans[16]=1, fans[17]=1; 
                mp[hashCode]=1; return 1; 
            }
        } // 我有王炸
        idx=0; 
        rep(i,3,15){
            if(last[i]==4 && siz==4){ idx=i; break; }
        } // 对手是炸
        if(idx){ // 我能不能压过
            rep(i,idx+1,15){
                if(xcard[i]==4) {
                    xcard[i]-=4; 
                    rep(j,3,17) tlast[j]=last[j], last[j]=0;
                    last[i]=4;  
                    tmp=search(ycard,xcard,last,0); 
                    xcard[i]+=4; 
                    rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                    if(tmp==2){
                        if(isFir) fans[i]=4; 
                        mp[hashCode]=1; return 1; 
                    }
                }
            }
            mp[hashCode]=2; return 2;
        }
        // 除了火箭和炸，我炸弹乱杀
        rep(i,3,15){
            if(xcard[i]==4) {
                xcard[i]-=4; 
                rep(j,3,17) tlast[j]=last[j], last[j]=0;
                last[i]=4;  
                tmp=search(ycard,xcard,last,0); 
                xcard[i]+=4; 
                rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                if(tmp==2){
                    if(isFir) fans[i]=4; 
                    mp[hashCode]=1; return 1; 
                }
            }
        }
        idx=0;
        rep(i,3,15){
            if(last[i]==4 && siz>4){ idx=i; break; }
        } // 炸弹带东西
        if(idx){ rep(i,idx+1,15){
            if(xcard[i]==4){
                xcard[i]=0; 
                if(siz==6){ // TODO 优化递归
                    rep(d1,3,17) if(xcard[d1]>=1) {
                        xcard[d1]--;
                        rep(d2,3,17){
                            if(xcard[d2]>=1){
                                xcard[d2]--;
                                rep(j,3,17) tlast[j]=last[j], last[j]=0;
                                last[i]=4; last[d1]++, last[d2]++;
                                tmp=search(ycard,xcard,last,0); 
                                rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                                xcard[d2]++;
                                if(tmp==2){
                                    if(isFir) fans[i]=4, fans[d1]++, fans[d2]++; 
                                    xcard[d1]++; xcard[i]=4; 
                                    mp[hashCode]=1; return 1; 
                                }
                            }
                        }
                        xcard[d1]++; 
                    }
                }
                else { // siz==8 // TODO 优化递归
                    rep(d1,3,17) if(xcard[d1]>=2) {
                        xcard[d1]-=2;
                        rep(d2,3,17){
                            if(xcard[d2]>=2){
                                xcard[d2]-=2;
                                rep(j,3,17) tlast[j]=last[j], last[j]=0;
                                last[i]=4; last[d1]+=2, last[d2]+=2;
                                tmp=search(ycard,xcard,last,0); 
                                rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                                xcard[d2]+=2;
                                if(tmp==2){
                                    if(isFir) fans[i]=4, fans[d1]+=2, fans[d2]+=2; 
                                    xcard[d1]+=2; xcard[i]=4; 
                                    mp[hashCode]=1; return 1; 
                                }
                            }
                        }
                        xcard[d1]+=2; 
                    }
                }
                xcard[i]=4; 
            }
        } mp[hashCode]=2; return 2;}
        if(maLast==3){ // 连续三个 不带，带1，带2
            idx=0, leng=1; 
            rep(i,3,17){
                if(last[i]==3){idx=i; break; }
            }
            if(idx) rep(i,idx+1,17){
                if(last[i]==3) leng++; 
                else break; 
            }
            if(idx){ 
            int funNum=0, funVec[1000][20]; 
            rep(i,idx+1,17){
                if(xcard[i]>=3){
                    rep(k,i,i+leng-1){
                        if(xcard[k]<3) break; 
                        if(k==i+leng-1){
                            rep(j,3,17) tlast[j]=last[j], last[j]=0, tcard[j]=xcard[j]; 
                            rep(j,i,k) xcard[j]-=3, tcard[j]-=3, last[j]+=3;
                            dfsTriplet(xcard,leng,(siz-leng*3)/leng);
                            funNum=vecNum; 
                            rep(o,1,vecNum) rep(j,3,17) funVec[o][j]=vec[o][j]; 
                            rep(o,1,funNum){
                                rep(j,3,17) xcard[j]-=funVec[o][j], last[j]+=funVec[o][j];
                                tmp=search(ycard,xcard,last,0); 
                                if(tmp==2){
                                    if(isFir) rep(j,3,17) fans[j]=last[j]; 
                                    rep(j,3,17) xcard[j]+=funVec[o][j]; 
                                    rep(j,i,k) xcard[j]+=3, tcard[j]+=3, last[j]-=3; 
                                    mp[hashCode]=1; return 1; 
                                } 
                            }
                            rep(j,i,k) xcard[j]+=3, tcard[j]+=3, last[j]-=3; 
                            rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                        }
                    }
                }
            } }
        }
        if(maLast==2 && siz>=6){ // 连对
            idx=0;
            rep(i,3,17) {
                if(last[i]==2){idx=i; break;}
            }
            if(idx) rep(i,idx+1,17){
                if(xcard[i]>=2){
                    leng=i+siz/2-1; 
                    rep(k,i,leng){
                        if(xcard[k]<2) break; 
                        if(k==leng){
                            rep(j,3,17) tlast[j]=last[j], last[j]=0; 
                            rep(j,i,k) xcard[j]-=2, last[j]+=2; 
                            tmp=search(ycard,xcard,last,0);
                            rep(j,i,k) xcard[j]+=2; 
                            rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                            if(tmp==2){
                                if(isFir) rep(j,i,k) fans[j]=1; 
                                mp[hashCode]=1; return 1;  
                            }
                        }
                    }
                }
            }
        }
        if(maLast==1 && siz>=5){ // 顺子
            idx=0;
            rep(i,3,17){
                if(last[i]==1){idx=i; break; }
            }
            if(idx) rep(i,idx+1,17){
                if(xcard[i]>=1){
                    rep(k,i,i+siz-1){
                        if(xcard[k]<1) break;
                        if(k==i+siz-1){ // i到k是我的出牌
                            rep(j,3,17) tlast[j]=last[j],last[j]=0;
                            rep(j,i,k) xcard[j]--,last[j]++;
                            tmp=search(ycard,xcard,last,0);
                            rep(j,i,k) xcard[j]++;
                            rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                            if(tmp==2){
                                if(isFir) rep(j,i,k) fans[j]=1; 
                                mp[hashCode]=1; return 1; 
                            } 
                        }
                    }
                }
            }
        } 
        if(siz==2){ // 对子
            idx=0; 
            rep(i,3,17){
                if(last[i]==2){idx=i; break; }
            }
            if(idx) rep(i,idx+1,17){
                if(xcard[i]>=2){
                    xcard[i]-=2;
                    rep(j,3,17) tlast[j]=last[j], last[j]=0;
                    last[i]=2; 
                    tmp=search(ycard,xcard,last,0); 
                    xcard[i]+=2; 
                    rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                    if(tmp==2){
                        if(isFir) fans[i]=2; 
                        mp[hashCode]=1; return 1; 
                    }
                }
            }
        }
        if(siz==1){ // 单个
            idx=0; 
            rep(i,3,17){
                if(last[i]==1){idx=i; break; }
            }
            if(idx) rep(i,idx+1,17){
                if(xcard[i]>=1){
                    xcard[i]--; 
                    rep(j,3,17) tlast[j]=last[j], last[j]=0; 
                    last[i]=1; 
                    tmp=search(ycard,xcard,last,0);
                    xcard[i]++; 
                    // cout<<"sear" <<tmp<<endl;
                    rep(j,3,17) last[j]=tlast[j], tlast[j]=0; 
                    if(tmp==2) {
                        if(isFir) fans[i]=1;
                        mp[hashCode]=1; return 1;
                    }
                }
            }
        }
        // cout<<"loss2"<<endl;
        mp[hashCode]=2; return 2;  // x is loss; 
    }
    else { // 我先出牌
        rep(i,3,17){ // 单个
            if(xcard[i]>=1){
                last[i]=1; xcard[i]--;
                tmp=search(ycard,xcard,last,0);
                last[i]=0; xcard[i]++; 
                if(tmp==2){
                    if(isFir) fans[i]=1;
                    mp[hashCode]=1; return 1;
                }
            }
        }
        rep(i,3,17){ // 对子
            if(xcard[i]>=2){
                last[i]=2; xcard[i]-=2;
                tmp=search(ycard,xcard,last,0);
                last[i]=0; xcard[i]+=2; 
                if(tmp==2){
                    if(isFir) fans[i]=2;
                    mp[hashCode]=1; return 1;
                }
            }
        }
        rep(i,3,17){ // 顺子
            if(xcard[i]>=1){
                rep(k,i+1,14){
                    if(xcard[k]<1) break; 
                    if(k-i+1>=5){
                        rep(j,i,k){last[j]=1, xcard[j]--; }
                        tmp=search(ycard,xcard,last,0); 
                        rep(j,i,k) last[j]=0, xcard[j]++; 
                        if(tmp==2){
                            if(isFir) rep(j,i,k)fans[j]=1; 
                            mp[hashCode]=1; return 1; 
                        }
                    }
                }
            }
        }
        rep(i,3,17){ // 连对
            if(xcard[i]>=2){
                rep(k,i+1,14){
                    if(xcard[k]<2) break; 
                    if(k-i+1>=3){
                        rep(j,i,k){last[j]=2, xcard[j]-=2; }
                        tmp=search(ycard,xcard,last,0); 
                        rep(j,i,k) last[j]=0, xcard[j]+=2; 
                        if(tmp==2){
                            if(isFir) rep(j,i,k) fans[j]=2; 
                            mp[hashCode]=1; return 1; 
                        }
                    }
                }
            }
        }
        int funNum=0, funVec[1000][20]; 
        rep(i,3,17){ // 三带
            if(xcard[i]>=3){
                rep(k,i,14){
                    if(xcard[k]<3) break; 
                    if(k-i+1>=1){
                        leng=k-i+1; 
                        rep(j,i,k){last[j]=3, xcard[j]-=3; }
                        tmp=search(ycard,xcard,last,0); 
                        if(tmp==2){
                            rep(j,i,k) last[j]=0, xcard[j]+=3;
                            if(isFir) rep(j,i,k) fans[j]=3; 
                            mp[hashCode]=1; return 1; 
                        }
                        // cout<<xcard<<" dfs "<<leng<<endl;

                        dfsTriplet(xcard,leng,1);
                        funNum=vecNum; 
                        rep(o,1,vecNum) rep(j,3,17) funVec[o][j]=vec[o][j]; 
                        rep(o,1,funNum){
                            rep(j,3,17) xcard[j]-=funVec[o][j], last[j]+=funVec[o][j];
                            tmp=search(ycard,xcard,last,0); 
                            if(tmp==2){
                                rep(j,i,k) xcard[j]+=3;
                                if(isFir) rep(j,3,17) fans[j]=last[j]; 
                                rep(j,3,17) xcard[j]+=funVec[o][j];
                                mp[hashCode]=1; return 1; 
                            } 
                            rep(j,3,17) xcard[j]+=funVec[o][j], last[j]-=funVec[o][j]; 
                        }
                        dfsTriplet(xcard,leng,2);
                        funNum=vecNum; 
                        rep(o,1,vecNum) rep(j,3,17) funVec[o][j]=vec[o][j]; 
                        rep(o,1,funNum){
                            rep(j,3,17) xcard[j]-=funVec[o][j], last[j]+=funVec[o][j];
                            tmp=search(ycard,xcard,last,0); 
                            if(tmp==2){
                                rep(j,i,k) xcard[j]+=3;
                                if(isFir) rep(j,3,17) fans[j]=last[j];
                                rep(j,3,17) xcard[j]+=funVec[o][j];
                                mp[hashCode]=1; return 1; 
                            } 
                            rep(j,3,17) xcard[j]+=funVec[o][j], last[j]-=funVec[o][j]; 
                        }
                        rep(j,i,k) last[j]=0;  
                        rep(j,i,k) xcard[j]+=3;
                    }
                }
            }
        }
        rep(i,3,17){ // 炸 
            if(xcard[i]>=4){
                last[i]=4, xcard[i]-=4; 
                tmp=search(ycard,xcard,last,0); 
                if(tmp==2){
                    if(isFir) fans[i]=4;
                    mp[hashCode]=1; xcard[i]+=4; return 1; 
                }
                dfsTriplet(xcard,2,1);
                funNum=vecNum; 
                rep(o,1,vecNum) rep(j,3,17) funVec[o][j]=vec[o][j]; 
                rep(o,1,funNum){
                    rep(j,3,17) xcard[j]-=funVec[o][j], last[j]+=funVec[o][j];
                    tmp=search(ycard,xcard,last,0); 
                    rep(j,3,17) xcard[j]+=funVec[o][j] ;
                    if(tmp==2){
                        if(isFir) rep(j,3,17) fans[j]=last[j]; 
                        mp[hashCode]=1; xcard[i]+=4; return 1; 
                    } 
                    rep(j,3,17) last[j]-=funVec[o][j];
                }
                dfsTriplet(xcard,2,2);
                funNum=vecNum; 
                rep(o,1,vecNum) rep(j,3,17) funVec[o][j]=vec[o][j]; 
                rep(o,1,funNum){
                    rep(j,3,17) xcard[j]-=funVec[o][j], last[j]+=funVec[o][j];
                    tmp=search(ycard,xcard,last,0); 
                    rep(j,3,17) xcard[j]+=funVec[o][j]; 
                    if(tmp==2){
                        if(isFir) rep(j,3,17) fans[j]=last[j]; 
                        mp[hashCode]=1; xcard[i]+=4; return 1; 
                    } 
                    rep(j,3,17) last[j]-=funVec[o][j];
                }
                last[i]=0; xcard[i]+=4;
            }
        }

        if(xcard[16]&&xcard[17]){ // 王炸
            last[16]=last[17]=1; 
            xcard[16]=xcard[17]=0; 
            tmp=search(ycard,xcard,last,0); 
            xcard[16]=xcard[17]=1; 
            last[16]=last[17]=0; 
            if(tmp==2){
                if(isFir) fans[16]=fans[17]=1;
                mp[hashCode]=1; return 1; 
            }
        }
        // printf("Loss!!\n");
        mp[hashCode]=2; return 2; // 所有出发都不能赢，则为输
    }

}


int main (){
    // freopen("tt.txt","r",stdin); 
    // freopen("tt2.txt","w",stdout); 
    Alice.readCard(); 
    Bob.readCard(); 
    // Last.readCard();
    Alice.debugHand(); 
    // Alice.test();
    Bob.debugHand();
    int cardA[20],cardB[20],emptyArr[20];
    rep(i,3,17) emptyArr[i]=0; 

    Alice.copyHand(cardA); 
    Bob.copyHand(cardB); 
    int finalAns=search(cardA,cardB,emptyArr,1);
    printf("=====================\n");
    printf("%d\n",finalAns); 
    int fanSiz=0; 
    rep(i,3,17){fanSiz+=fans[i]; printf("%d:%d  ",i,fans[i]);}
    if(!fanSiz) printf("Skip!");
    printf("\n");
    // return 0;
    while(1){
        // Alice.copyHand(cardA); 
        // Bob.copyHand(cardB); 
        Last.readCard(); 
        Last.copyHand(emptyArr); 
        rep(i,3,17) cardA[i]-=fans[i], fans[i]=0, cardB[i]-=emptyArr[i]; 
        rep(i,3,17) printf("%d ",cardA[i]); cout<<endl;
        rep(i,3,17) printf("%d ",cardB[i]); cout<<endl;
        rep(i,3,17) printf("%d ",emptyArr[i]); cout<<endl;
        finalAns=search(cardA,cardB,emptyArr,1); 
        printf("=====================\n");

        printf("%d\n",finalAns); fanSiz=0; 
        rep(i,3,17){fanSiz+=fans[i]; printf("%d:%d  ",i,fans[i]);}
        if(!fanSiz) printf("Skip!");
        printf("\n");
        // break;
    }
    
    printf("Finish!!!!!!\n");
    return 0; 
}

void HandCard::prints(){
    printf("SDG");
    cout<<num<<endl;
    return ;
}

void User::debugHand(){
    printf("num is %d\n",ptrHand->num); 
    // printf("comb is %d\n",ptrHand->min_comb); 
    rep(i,3,17){
        printf("%d:%d  ",i,ptrHand->card[i]); 
    }
    printf("\n");
    rep(i,1,ptrHand->num){
        printf("%d ",ptrHand->cards[i]); 
    }
    printf("\n");
}

void User::readCard(){
    char ch[60]; 
    int n; 
    ptrHand=new HandCard(); 
    scanf("%s",ch+1); 
    n=strlen(ch+1); 
    rep(i,1,n){
        if(isdigit(ch[i])){
            if(ch[i]=='0') ch[i]+=10; 
            if(ch[i]=='2') ch[i]+=13; 
            ptrHand->cards[++ptrHand->num]=ch[i]-'0';
        }
        else {
            if(ch[i]=='J') ptrHand->cards[++ptrHand->num]=11;
            if(ch[i]=='Q') ptrHand->cards[++ptrHand->num]=12;
            if(ch[i]=='K') ptrHand->cards[++ptrHand->num]=13;
            if(ch[i]=='A') ptrHand->cards[++ptrHand->num]=14;
            if(ch[i]=='B') ptrHand->cards[++ptrHand->num]=16; // Black
            if(ch[i]=='R') ptrHand->cards[++ptrHand->num]=17; // Red
        }
    }
    sort(1+ptrHand->cards,1+ptrHand->cards+ptrHand->num);
    rep(i,1,ptrHand->num){
        ptrHand->card[ptrHand->cards[i]]++; 
    }
}

void User::copyHand(int *arr){
    // HandCard *ptrHand; 
    rep(i,3,17) arr[i]=ptrHand->card[i];
}

void User::checkLegal(){
    return ;
}