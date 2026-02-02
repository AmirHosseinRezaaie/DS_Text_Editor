# ویرایشگر متن ساده با Undo / Redo

Text Editor – Command Line – C++

این پروژه یک ویرایشگر متن ساده در محیط خط فرمان است که عملیات زیر را پشتیبانی می‌کند:

- insert <position> <text>
- delete <position> <length>
- copy <position> <length>
- paste <position>
- print
- undo
- redo
- exit / quit

ساختمان داده‌ها:
- متن اصلی → std::string
- undo → std::stack<Action>
- redo → std::stack<Action>
- کلیپ‌بورد → std::string

نحوه اجرا:
make
make run
make clean

یا دستی:
g++ -std=c++17 -Wall -Wextra src/*.cpp -o text-editor
./text-editor    یا    text-editor.exe

ساختار پوشه:
text-editor-cpp/
├── Makefile
├── README.md
├── src/
│   ├── main.cpp
│   ├── editor.h
│   ├── editor.cpp
│   └── action.h
├── build/
└── bin/

نکات تحویل:
- کامپایل با make بدون خطا
- توضیح انتخاب ساختمان داده
- مدیریت خطاها (موقعیت نامعتبر، undo خالی و ...)
- پیام‌های خطای مناسب

امیرحسین رضایی
شماره دانشجویی: 403541474
زمستان 1404