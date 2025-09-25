Giới thiệu

Dự án này xây dựng một máy tính cầm tay đơn giản dựa trên vi điều khiển STM32, sử dụng bàn phím ma trận (Keypad) để nhập dữ liệu và LCD 16x2 để hiển thị kết quả.
Mục tiêu:

Thực hành lập trình trên STM32 với FreeRTOS.

Xử lý nhập liệu từ bàn phím.

Thực hiện các phép tính số học cơ bản và phương trình bậc 1, bậc 2.

Phần cứng sử dụng

STM32 (dòng STM32F103C8T6 “Blue Pill”)

Bàn phím ma trận 4x4

Màn hình LCD 16x2 (HD44780 driver)

Nguồn 5V + breadboard / PCB custom

Công nghệ & Công cụ

Ngôn ngữ: Embedded C

Framework: FreeRTOS (task scheduling)

IDE: STM32CubeIDE / Keil C

Thiết kế mạch: Altium Designer

Tính năng chính

Nhập số và phép toán từ Keypad.

Hiển thị quá trình nhập và kết quả trên LCD 16x2.

Hỗ trợ:

Cộng, trừ, nhân, chia

Giải phương trình bậc nhất, bậc hai

Xử lý chống dội phím (debounce) để nhập chính xác.

FreeRTOS: sử dụng một task duy nhất để xử lý tuần tự:

Đọc phím → xử lý phép tính → cập nhật LCD.

Cách triển khai: 

clone repo

Mở project trong STM32CubeIDE.

Build & flash code vào STM32.

Cách sử dụng

Bấm phím số → hiển thị trên LCD.

Bấm các phím +, -, *, / để chọn phép tính.

Bấm = để hiển thị kết quả.

Với phương trình: nhập dạng ax+b=0 hoặc ax^2+bx+c=0, máy sẽ tính nghiệm.

Demo: đính kèm ở folder video demo ở trên

Hướng phát triển

Mở rộng chức năng (logarit, sin/cos, ma trận).

Nâng cấp giao diện sang LCD đồ họa hoặc TFT

Tác giả: Nguyễn Hoàng Minh Quốc
