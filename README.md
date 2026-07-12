# rcan

CAN 2.0B Activeを使用した小規模ロボット制御用通信プロトコル。

マスタースレーブでの使用を想定しています。

## Network

ネットワークの構成には拡張フォーマットデータフレームを使用します。

### Node identifier

ネットワーク内の各ノードは8bitのIDを持ちます。ノードのIDには**0x00 ~ 0xfd**を用いることができます。**0xfe**はヌル(ノード指定なし)に、**0xff**はブロードキャスト(全ノード指定)に割り振られます。

マスターからの全体指令にはブロードキャストID 0xFFが使用可能です。又、ヌルIDへの送信は配信として監視し、情報を取得できます。

### Identifier conflict resolution

ノードIDが衝突した場合の規定はありません。

### Frame identifier format

拡張フォーマットデータフレームのID(29bit)は以下のようにフォーマットされます。

```text
| 13bit data | 8bit source ID | 8bit target ID |
```

- `data`領域にはセッション制御やアプリケーション制御に用いるデータが格納されます。
- `source ID`には送信者のノードIDが格納されます。
- `target ID`には受信者のノードIDが格納されます。

## Control

ネットワーク構成用にフォーマットされた拡張フォーマットデータフレームのIDの内、13bit data領域を使用します。

要求に対する応答は全て`ACK`または`NAK`で応答されます。応答のあるコマンドは一度に複数扱うことはできません。

### Data space format

```text
| 2bit priority | 3bit category | 8bit command |
```

- `priority`はコマンドの優先度を示します。0 ~ 3です。
- `category`はコマンドの分類を示します。0 ~ 7です。
- `command`はコマンドを示します。0 ~ 255です。

### Priority

| priority | function |
| --- | --- |
| 0 | 緊急性の高いもの。 |
| 1 | 終了等の優先すべきもの。 |
| 2 | 定期的に送信するもの。 |
| 3 | 開始等優先の必要ないもの。 |

### Category

| num | category | function |
| --- | --- | --- |
| 0 | SYSTEM | 状態管理。 |
| 1 | CONFIG | 各種設定。 |
| 2 | TARGET | 制御目標指定。 |
| 3 | FEEDBACK | 制御状態配信。 |
| 4 | ASK | 情報取得。 |
| 6 | RESERVED | 予約済み。 |
| 7 | RESERVED | 予約済み。 |

### Command

| priority | category | command | command hex | data hex | response | function |
| --- | --- | --- | --- | --- | --- | --- |
| 3 | SYSTEM | ACTIVATE | 0x00 | 0x1800 | enable | 制御開始。 |
| 1 | SYSTEM | DEACTIVATE | 0x01 | 0x0801 | enable | 制御正常終了。 |
| 0 | SYSTEM | TERMINATE | 0x02 | 0x0002 | disable | 制御放棄、強制終了。 |
| 1 | SYSTEM | RESET | 0x03 | 0x0803 | disable | ソフトウェアリセット。 |
| 2 | SYSTEM | ACK | 0x10 | 0x1010 | this | 肯定応答。 |
| 1 | SYSTEM | NAK | 0x11 | 0x0811 | this | 否定応答。 |
| 2 | SYSTEM | HEARTBEAT | 0x20 | 0x1020 | disable | 生存報告。 |
| 0 | SYSTEM | ERROR | 0x21 | 0x0821 | disable | 異常報告。 |
| 3 | ASK | PING | 0x00 | 0x1c00 | enable | 疎通確認。 |
