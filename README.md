# 斗地主
嘿！ 我是皮虾，帮我点个star！
这个项目目前仅支持欢乐斗地主的残局明牌双人对战模式

# how to use
3-9用数字表示， 10是0，11是J，12是Q，13是K，14是A，15是2，小王B，大王R
输入双方手牌（先输入先手）
QJJ0988744
RBAA97633
然后代码输出Win or Loss
并输出你应该走的方案
然后你继续输入对手的走法（比如RB，不出输入N）
循环直到游戏结束

# Note

Comb 

single pair triplet triplet-single triplet-pair sequence sequence-pair sequence-triplet sequence-triplet-single sequence-triplet-pair bomb rocket quadplex 

可以先统计顺子，再统计几组4个，几组3个，对子，单个。

优化
统计出所有可以赢的下法

游戏规则细节：
默认不能两个炸带4张。 不能带一个对一个单
默认王炸不能带牌。

# Future Work
1. 从两人明牌到三人明牌 （创新性太小）
2. 从两人明牌到三人暗牌 （难度太大，目前思路可能要上AI？）
 