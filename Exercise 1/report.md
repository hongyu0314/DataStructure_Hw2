### 題目問題：What is the total input time for phase two of external sorting if a k-way merge is used with internal memory partitioned into input/output buffers to permit overlap of input, output, and CPU processing as in Buffering (Program 7.21)?

$n$: 總記錄數

$S$: 內存容量

$m$: runs數量

$k$: k-way merge

$ts$: seek time

$tl$: latency time

$tt$: transmission time per record

### 解釋：

1. 在k-way merge中， $S$ 個記錄的內存被分為 $k$ 個input buffers和1個output buffer
2. 每個input buffer大小約為 $S/k$ 個記錄
3. 需要 $⌈n/(S/k)⌉$ 次磁盤讀取操作
4. 每次讀取的時間成本： $ts + tl$ （固定成本）
5. 傳輸n個記錄的時間： $n × tt$ 

答案： $⌈n/(S/k)⌉ × (ts + tl) + n × tt$
