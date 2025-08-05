# راه‌های ساده برای ساخت APK

## راه 1: استفاده از GitHub (رایگان و آنلاین) ⭐ توصیه می‌شم

1. **پروژه رو به GitHub آپلود کن:**
   ```bash
   git init
   git add .
   git commit -m "Initial commit"
   git remote add origin https://github.com/[username]/toopan2d.git
   git push -u origin main
   ```

2. **GitHub Actions خودکار APK رو می‌سازه:**
   - به تب "Actions" برو
   - کار build رو اجرا کن
   - APK رو دانلود کن

## راه 2: نصب سریع ابزارها (10 دقیقه)

1. **Java نصب کن:**
   - برو به: https://adoptium.net/temurin/releases/?version=17
   - دانلود و نصب کن

2. **Android SDK نصب کن:**
   ```bash
   quick_setup.bat
   ```

3. **APK بساز:**
   ```bash
   build_apk.bat
   ```

## راه 3: استفاده از آنلاین بیلدر

1. **Replit.com:**
   - پروژه رو آپلود کن
   - Android template استفاده کن

2. **CodeSandbox:**
   - پروژه رو import کن
   - Build کن

## راه 4: استفاده از APK Builder آنلاین

1. برو به: https://www.apkbuilder.online/
2. پروژه رو zip کن و آپلود کن
3. APK رو دانلود کن

## راه 5: Manual Build (بدون ابزار اضافی)

اگه هیچ‌کدوم کار نکرد، یه APK ساده می‌سازم فقط با Java code (بدون C):