# BTL_snake_game
# 1. Giới thiệu chung
1. Làm game về rắn săn mồi cổ điển
2. Sử dụng ngôn ngữ C++ và đồ họa SFML https://www.sfml-dev.org/tutorials/2.5/
3. Âm thanh và hình ảnh lấy trên internet
# 2. Cài đặt chương trình
1. Tải file source code game trong link github bằng cách chọn Code->Download Zip
2. Tải bộ biên dịch SFML tại https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-win32/seh/x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z/download
3. Giải nén file BTL_snake-game.rar và file biên dịch SFML bên trên
4. Sau khi giải nén file biên dịch SFML, mở file mingw64, chọn thư mục bin. Copy đường dẫn đến thư mục bin này. Nhấn phím Window, tìm kiếm tên Edit environment variables for your account->User variables for DELL->Path->New->Paste dường dẫn vừa copy vào->OK->OK
5. Mở file BTL_snake_game-main, đưa chuột đến khoảng trống trong file. Giữ phím Shift và ấn chuột phải, chọn Open PowerShell window here
6. Sau khi cửa sổ Windows PowerShell hiện lên, gõ lệnh mingw32-make, đợi biên dịch xong ta mở file main.exe để chơi game

# 3. Cách chơi
1. Điều khiển rắn bằng phím Left, Right, Up, Down để ăn táo
2. Có 4 level game, sau mỗi màn và mỗi khi ăn táo, tốc độ rắn sẽ tăng
3. Kết thúc game khi rắn đâm vào tường hoặc đâm vào thân
# 4. Các chức năng đã cài đặt
1. Hình ảnh, nhạc, sound effect
2. Tạm dừng game
3. Có nhiều màn chơi
4. Video demo https://youtu.be/ByONL_t0YXM
# 5. Kỹ thuật lập trình
1. Mảng, con trỏ, class, enum, hàng đợi,...
2. Thư viện đồ họa SFML
# 6. Kết luận
1. Đồ họa game và âm thanh ở mức ổn
2. Có tham khảo trên youtube
3. Hướng phát triển: Thêm các chức năng cho game, thêm highscore, nhập tên người chơi, thêm level, tối ưu hóa code
