### 問題（a）： What is the total input time for phase two of external sorting if a k-way merge is used with internal memory partitioned into input/output buffers to permit overlap of input, output, and CPU processing as in Buffering (Program 7.21)?

* $n$: 總記錄數

* $S$: 內存容量

* $m$: runs數量

* $k$: k-way merge

* $ts$: seek time

* $tl$: latency time

* $tt$: transmission time per record

### 解釋：

1. 在k-way merge中， $S$ 個記錄的內存被分為 $k$ 個input buffers和1個output buffer
2. 每個input buffer大小約為 $S/k$ 個記錄
3. 需要 $⌈n/(S/k)⌉$ 次磁盤讀取操作
4. 每次讀取的時間成本： $ts + tl$ （固定成本）
5. 傳輸n個記錄的時間： $n × tt$ 

## 答案： $⌈n/(S/k)⌉ × (ts + tl) + n × tt$


### 問題（b）： Obtain a rough plot of the total input time, $tinput$ , versus $k$ . Will there always be a value of $k$ for which $tCPU$ approx $tinput$ ?

#### 課本給的參數

* $s = 80 ms = 0.08 sec$
* $tl = 20 ms = 0.02 sec$
* $n = 200,000$
* $m = 64$
* $tt = 10⁻³ sec/record$
* $S = 2000$


#### 計算 $tinput$ (代入答案（a）的公式): 

$tinput = ⌈200,000k/2000⌉ × (0.08 + 0.02) + 200,000 × 0.001 = ⌈100k⌉ × 0.1 + 200 = 100k × 0.1 + 200 = 10k + 200$ 

設 $tCPU = C$ (常數)，則：
$C ≈ 10k + 200 , k ≈ (C - 200)/10$

只要 $tCPU > 200$ 秒，就存在 $k$ 值,
$k$ 值為： $k = (tCPU - 200)/10$ 

因為 $k$需是正整數且 $k ≤ m = 64$ ,所以 $tCPU > 200$ (保證 $k$ > 0)
$tCPU ≤ 840$ (保證 $k$ ≤ 64)

## 答案：當 $200 < tCPU ≤ 840$ 秒時，是存在合適的 $k$ 值使 $tCPU ≈ tinput$
