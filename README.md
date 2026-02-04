<!DOCTYPE html>
<html lang="fa" dir="rtl">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- <title>ویرایشگر متن پیشرفته - پروژه ساختمان داده</title> -->
    <!-- <style>
        :root {
            --primary: #2563eb;
            --secondary: #7c3aed;
            --success: #10b981;
            --warning: #f59e0b;
            --danger: #ef4444;
            --dark: #1f2937;
            --light: #f9fafb;
            --code-bg: #1e1e1e;
        }
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.8;
            color: var(--dark);
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
        }
        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
        .header {
            background: white;
            border-radius: 20px;
            padding: 40px;
            margin-bottom: 30px;
            box-shadow: 0 20px 60px rgba(0,0,0,0.1);
            text-align: center;
            border: 2px solid var(--primary);
        }
        .title {
            color: var(--primary);
            font-size: 2.5rem;
            margin-bottom: 10px;
            background: linear-gradient(90deg, var(--primary), var(--secondary));
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
        }
        .subtitle {
            color: var(--dark);
            font-size: 1.2rem;
            opacity: 0.8;
            margin-bottom: 20px;
        }
        .card {
            background: white;
            border-radius: 15px;
            padding: 30px;
            margin-bottom: 25px;
            box-shadow: 0 10px 40px rgba(0,0,0,0.08);
            transition: transform 0.3s ease;
            border: 1px solid #e5e7eb;
        }
        .card:hover {
            transform: translateY(-5px);
            box-shadow: 0 15px 50px rgba(0,0,0,0.12);
        }
        .card-title {
            color: var(--primary);
            font-size: 1.5rem;
            margin-bottom: 15px;
            padding-bottom: 10px;
            border-bottom: 3px solid var(--primary);
            display: flex;
            align-items: center;
            gap: 10px;
        }
        .card-title i {
            font-size: 1.8rem;
        }
        .features-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 20px;
            margin: 30px 0;
        }
        .feature-item {
            background: white;
            padding: 25px;
            border-radius: 12px;
            border-left: 4px solid var(--primary);
            box-shadow: 0 5px 20px rgba(0,0,0,0.05);
        }
        .feature-item h4 {
            color: var(--primary);
            margin-bottom: 10px;
            font-size: 1.2rem;
        }
        .command-list {
            background: var(--code-bg);
            color: #d4d4d4;
            padding: 25px;
            border-radius: 10px;
            margin: 20px 0;
            font-family: 'Consolas', 'Monaco', monospace;
            overflow-x: auto;
        }
        .command {
            color: #569cd6;
            margin-bottom: 8px;
            padding: 5px 0;
        }
        .command span {
            color: #9cdcfe;
        }
        .highlight {
            background: linear-gradient(120deg, #a5b4fc30 0%, #c4b5fd30 100%);
            padding: 15px;
            border-radius: 10px;
            margin: 15px 0;
            border-right: 4px solid var(--secondary);
        }
        .test-case {
            background: #f8fafc;
            border: 2px solid #e2e8f0;
            border-radius: 10px;
            padding: 20px;
            margin: 15px 0;
        }
        .test-input {
            color: var(--primary);
            font-weight: bold;
            margin-bottom: 5px;
        }
        .test-output {
            color: var(--success);
            font-family: monospace;
            background: #1e293b;
            padding: 15px;
            border-radius: 8px;
            margin-top: 10px;
        }
        .complexity-table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }
        .complexity-table th {
            background: var(--primary);
            color: white;
            padding: 15px;
            text-align: right;
        }
        .complexity-table td {
            padding: 12px 15px;
            border-bottom: 1px solid #e5e7eb;
        }
        .complexity-table tr:nth-child(even) {
            background: #f8fafc;
        }
        .complexity-table tr:hover {
            background: #e0f2fe;
        }
        .badge {
            display: inline-block;
            padding: 5px 12px;
            border-radius: 20px;
            font-size: 0.85rem;
            font-weight: bold;
            margin: 0 5px;
        }
        .badge-primary {
            background: var(--primary);
            color: white;
        }
        .badge-success {
            background: var(--success);
            color: white;
        }
        .badge-warning {
            background: var(--warning);
            color: white;
        }
        .footer {
            text-align: center;
            padding: 30px;
            margin-top: 50px;
            color: white;
            background: rgba(0,0,0,0.2);
            border-radius: 15px;
        }
        @media (max-width: 768px) {
            .container {
                padding: 10px;
            }
            .header {
                padding: 20px;
            }
            .title {
                font-size: 2rem;
            }
            .features-grid {
                grid-template-columns: 1fr;
            }
        }
    </style> -->
</head>
<body>
    <div class="container">
        <header class="header">
            <h1 class="title">ویرایشگر متن پیشرفته</h1>
            <p class="subtitle">پروژه درس ساختمان داده - سیستم ویرایش متن با قابلیت‌های Undo/Redo و AutoComplete</p>
            <div style="margin-top: 20px;">
                <span class="badge badge-primary">C++17</span>
                <span class="badge badge-success">Trie Data Structure</span>
                <span class="badge badge-warning">CLI Application</span>
            </div>
        </header>
        <section class="card">
            <h2 class="card-title">📋 معرفی پروژه</h2>
            <p>این پروژه یک ویرایشگر متن خط فرمانی (CLI) است که با زبان ++C پیاده‌سازی شده و از قابلیت‌های پیشرفته‌ای مانند Undo/Redo، AutoComplete و مدیریت تاریخچه ویرایش پشتیبانی می‌کند. هدف این پروژه نشان دادن کاربرد عملی ساختمان داده‌ها در طراحی سیستم‌های واقعی است.</p>
        </section>
        <section class="card">
            <h2 class="card-title">✨ ویژگی‌های اصلی</h2>
            <div class="features-grid">
                <div class="feature-item">
                    <h4>📝 ویرایش متن پایه</h4>
                    <p>درج، حذف، کپی و پیست متن در هر موقعیت دلخواه</p>
                </div>
                <div class="feature-item">
                    <h4>↩️ سیستم Undo/Redo</h4>
                    <p>بازگردانی و تکرار عملیات با محدودیت هوشمند ۳ عملیات</p>
                </div>
                <div class="feature-item">
                    <h4>🔤 AutoComplete هوشمند</h4>
                    <p>پیشنهاد کلمات با استفاده از ساختار داده Trie</p>
                </div>
                <div class="feature-item">
                    <h4>🌳 نمایش ساختار Trie</h4>
                    <p>نمایش گرافیکی درخت کلمات و مسیرهای موجود</p>
                </div>
            </div>
        </section>
        <section class="card">
            <h2 class="card-title">⌨️ دستورات قابل استفاده</h2>
            <div class="command-list">
                <div class="command">print</div>
                <div class="command">insert <span>&lt;position&gt; &lt;text&gt;</span></div>
                <div class="command">delete <span>&lt;position&gt; &lt;length&gt;</span></div>
                <div class="command">copy <span>&lt;position&gt; &lt;length&gt;</span></div>
                <div class="command">paste <span>&lt;position&gt;</span></div>
                <div class="command">undo / redo</div>
                <div class="command">auto <span>&lt;prefix&gt;</span></div>
                <div class="command">showtrie <span>[-a]</span></div>
                <div class="command">history</div>
                <div class="command">exit / quit</div>
            </div>
        </section>
        <section class="card">
            <h2 class="card-title">🧪 نمونه اجرا و تست</h2>
            <div class="test-case">
                <div class="test-input">ورودی:</div>
                <div class="command">insert 0 Start testing</div>
                <div class="command">insert 5  DS project</div>
                <div class="command">print</div>
                <div class="command">delete 5 7</div>
                <div class="command">copy 3 7</div>
                <div class="command">paste 0</div>
                <div class="command">copy 7 2</div>
                <div class="command">paste 0</div>
            </div>
            <div class="highlight">
                <strong>خروجی مورد انتظار:</strong>
                <div class="test-output">
                    Text: "Start testing"<br>
                    Text: "Start DS project testing"<br>
                    Text: "Start DS project testing"<br>
                    Text: "Start project testing"<br>
                    Copied!<br>
                    Text: "rt projStart project testing"<br>
                    Copied!<br>
                    Text: "Start rt projStart project testing"
                </div>
            </div>
        </section>
        <section class="card">
            <h2 class="card-title">⚙️ تحلیل پیچیدگی زمانی</h2>
            <table class="complexity-table">
                <thead>
                    <tr>
                        <th>عملیات</th>
                        <th>پیچیدگی زمانی</th>
                        <th>پیچیدگی حافظه</th>
                        <th>توضیح</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td>Insert</td>
                        <td>O(n)</td>
                        <td>O(1)</td>
                        <td>جابجایی رشته در حافظه</td>
                    </tr>
                    <tr>
                        <td>Delete</td>
                        <td>O(n)</td>
                        <td>O(1)</td>
                        <td>جابجایی رشته در حافظه</td>
                    </tr>
                    <tr>
                        <td>Copy</td>
                        <td>O(k)</td>
                        <td>O(k)</td>
                        <td>k = طول بخش کپی شده</td>
                    </tr>
                    <tr>
                    <td>Paste</td>
                        <td>O(n)</td>
                        <td>O(1)</td>
                        <td>درج در متن اصلی</td>
                    </tr>
                    <tr>
                        <td>Undo/Redo</td>
                        <td>O(1)</td>
                        <td>O(1)</td>
                        <td>دسترسی به عمل‌های ذخیره شده</td>
                    </tr>
                    <tr>
                        <td>AutoComplete جستجو</td>
                        <td>O(p)</td>
                        <td>O(1)</td>
                        <td>p = طول پیشوند</td>
                    </tr>
                    <tr>
                        <td>AutoComplete پیشنهاد</td>
                        <td>O(k × l)</td>
                        <td>O(k × l)</td>
                        <td>k = تعداد کلمات، l = میانگین طول</td>
                    </tr>
                </tbody>
            </table>
        </section>
        <section class="card">
            <h2 class="card-title">🏗️ ساختار پروژه</h2>
            <div class="highlight">
                <pre style="font-family: monospace; white-space: pre-wrap;">
📦 text-editor-project
├── 📂 src/
│   ├── main.cpp              # نقطه شروع برنامه
│   ├── trie.cpp              # پیاده‌سازی ساختار Trie
│   └── vector.cpp           # نسخه جایگزین با vector
├── 📂 include/
│   └── trie.h               # هدر فایل Trie
├── 📂 build/                # فایل‌های object
├── 📂 bin/                  # فایل اجرایی
├── 📂 tests/                  # فایل تست
│   ├── test.txt              # نمونه های تست
├── 📜 Makefile              # فایل ساخت
├── 📜 README.md             # مستندات
                </pre>
            </div>
        </section>
        <section class="card">
            <h2 class="card-title">🚀 نحوه اجرا</h2>
            <div class="highlight">
                <h4>کامپایل پروژه:</h4>
                <div class="command">make</div>
                <div class="command"># یا</div>
                <div class="command">make build-string && build-vector</div>
                <h4 style="margin-top: 20px;">اجرای برنامه:</h4>
                <div class="command">cd bin</div>
                <div class="command">./string</div>
                <div class="command"># یا</div>
                <div class="command">./vector</div>
                <h4 style="margin-top: 20px;">پاکسازی فایل‌های build:</h4>
                <div class="command">make clean</div>
            </div>
        </section>
        <section class="card">
            <h2 class="card-title">📊 آمار فنی</h2>
            <div class="features-grid">
                <div class="feature-item">
                    <h4>📏 خطوط کد</h4>
                    <p>حدود ۱۲۰۰ خط کد ++C</p>
                </div>
                <div class="feature-item">
                    <h4>🗃️ ساختار داده‌ها</h4>
                    <p>۴ ساختار داده اصلی: string, deque, Trie, stack</p>
                </div>
                <div class="feature-item">
                    <h4>📚 کلمات دیکشنری</h4>
                    <p>بیش از ۲۰۰ کلمه انگلیسی پرکاربرد</p>
                </div>
                <div class="feature-item">
                    <h4>⚡ کارایی</h4>
                    <p>Undo/Redo با پیچیدگی O(1)</p>
                </div>
            </div>
        </section>
        <footer class="footer">
            <div class="features-grid">
            <p>پروژه درس ساختمان داده - ویرایشگر متن پیشرفته</p>
            <p>امیرحسین رضایی</p>
            <p>شماره دانشجویی: 403541474</p>
            <p>پیاده‌سازی شده با ❤️ و ++C</p>
            <p> دانشگاه علم و صنعت ایران</p>
            <p>© 2026 - دانشکده مهندسی کامپیوتر</p>
        </footer>
    </div>
</body>
</html>