# Json String Normalization

## 问题
```
如果用json传递数据，数据必须是字符串，但有的字符会与json自己的字符发生冲突，因此需要转义输入的字符串数据，但转义会降低可读性，如果不想转义，可否设计一种编码格式，将字符串编码成对于json是合格的字符串，然后封装成json数据并传递。对于接收数据的那一方，需要从json中提取字符串，并再次解码得到原始字符串。如果可以，请用C++语言实现这种字符串编码和解码方案。
```
> 该方案主要由人工智能实现，代码经过人类审查和调整。

## 方案设计与实现
核心思路：JSON 字符串值中只有三类字符是"危险"的——"（闭合引号）、\（转义引导符）、控制字符 U+0000~U+001F。其余可打印 ASCII 都可直接出现。因此设计一种类百分号编码 %XX：把所有危险字符连同作为编码标记的 % 本身，统一编成 %XX（两位大写十六进制）。

## 编码规则
|原始字符类别                                   | 处理方式             |
|----------------------------------------------|---------------------|
|可打印 ASCII（0x20~0x7E），且非 "、\、%         | 保持原样             |
|"、\、%                                       | 编码为 %22、%5C、%25 |
|控制字符 0x000x1F、0x7F、非 ASCII 字节 0x800xFF| 编码为 %XX           |
----------------------------------------------------------------------

编码后字符串的字符集只含：可打印 ASCII（除 "、\、%）+ %（作为标记）。其中不含 "、\、任何控制字符，所以可直接作为 JSON 字符串值塞进去，JSON 解析器无需做任何反斜杠转义——这正是"不想转义"要达到的效果。

## 关键设计点
% 自身也要编码为 %25，否则解码时无法区分"原始 %"与"编码标记 %"。

解码严格校验：% 后必须跟两位合法十六进制，且编码串不应出现 "/\/控制字符/非 ASCII，否则返回 false，保证数据完整性可检测。

英文文本基本原样保留（可读性好）；中文/二进制会展开为 %XX 序列（以通用性换取这部分可读性，但保证任意字节都能无损传输）。

```
Design Purpose:
  To encode any string into a “JSON-safe” string so that it can appear 
  directly as a JSON string value without relying on JSON's own backslash 
  escaping (\", \\, \n, etc.).

  This also makes it easier for users to encode arbitrary data types 
  (such as regular expressions, images, audio) into valid JSON strings 
  for transmission via JSON.

Encoding Rules (Percent-encoding %XX):
  - “Safe characters” remain unchanged: printable ASCII characters (0x20–0x7E) other than ‘"’, ‘\’, and ‘%’.
  - All other characters (i.e., ‘"’, ‘\’, ‘%’, control characters 0x00–0x1F and 0x7F, and all non-ASCII bytes
    0x80–0xFF) are uniformly encoded as %XX (where XX is a two-digit uppercase hexadecimal number).

The character set of the encoded string contains only:
  1) characters in printable ASCII other than ‘"’, ‘\’, and ‘%’;
  2) ‘%’ as an encoding marker (followed by two hexadecimal digits).
  This set does not include ‘"’, ‘\’, or any control characters, so it can be placed directly within a JSON string value,
  without requiring any further escaping by the JSON parser; end-to-end transmission is controlled solely by this class.

```
