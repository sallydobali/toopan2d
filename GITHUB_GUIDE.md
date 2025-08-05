# 🎮 راهنمای کامل GitHub Actions برای Toopan2D

## 🚀 مراحل ساخت APK با GitHub Actions

### **مرحله 1: آپلود پروژه به GitHub**

#### A) اگه GitHub account نداری:
1. برو به [github.com](https://github.com)
2. روی "Sign up" کلیک کن
3. اطلاعات رو پر کن و ثبت‌نام کن

#### B) ساخت Repository جدید:
1. وارد GitHub شو
2. روی "+" بالا راست کلیک کن
3. "New repository" رو انتخاب کن
4. اسم: `toopan2d`
5. توضیحات: `2.5D Soccer Game for Android`
6. Public انتخاب کن (رایگان)
7. "Create repository" کلیک کن

### **مرحله 2: آپلود فایل‌ها**

#### روش آسان (Web Interface):
1. روی "uploading an existing file" کلیک کن
2. همه فایل‌های پروژه رو drag & drop کن
3. پیام commit: `Initial commit - Toopan2D Soccer Game`
4. "Commit changes" کلیک کن

#### فایل‌های مهم که حتماً آپلود کن:
```
✅ src/ (پوشه کامل)
✅ build.gradle
✅ build_simple.gradle  
✅ CMakeLists.txt
✅ gradlew.bat
✅ gradle/ (پوشه کامل)
✅ .github/ (پوشه کامل)
✅ AndroidManifest.xml
✅ README.md
```

### **مرحله 3: اجرای GitHub Actions**

#### A) خودکار (توصیه می‌شه):
- GitHub Actions خودکار شروع می‌شه
- به تب "Actions" برو
- workflow رو مشاهده کن

#### B) دستی:
1. به تب "Actions" برو
2. "Build Simple Android APK" رو انتخاب کن
3. "Run workflow" کلیک کن
4. "Run workflow" سبز رو کلیک کن

### **مرحله 4: دانلود APK**

1. منتظر بمون تا build تموم بشه (5-10 دقیقه)
2. وقتی تموم شد، روی workflow کلیک کن
3. تو بخش "Artifacts" APK رو پیدا کن
4. روی `toopan2d-simple-debug` کلیک کن
5. فایل ZIP دانلود می‌شه
6. ZIP رو extract کن
7. فایل APK آمادهست!

## 🎯 **دو نوع Build موجوده:**

### **1. Simple Build (توصیه می‌شه)**
- **فایل**: `.github/workflows/build-simple.yml`
- **زمان**: 5-7 دقیقه
- **حجم**: کمتر
- **فیچرها**: بازی Java ساده، کاملاً کار می‌کنه

### **2. Full Build (پیشرفته)**
- **فایل**: `.github/workflows/build.yml`
- **زمان**: 10-15 دقیقه  
- **حجم**: بیشتر
- **فیچرها**: بازی C کامل با OpenGL

## 🔧 **عیب‌یابی:**

### اگه Build شکست خورد:
1. به تب "Actions" برو
2. روی build شکست‌خورده کلیک کن
3. لاگ‌ها رو بررسی کن
4. معمولاً مشکل از:
   - فایل‌های ناقص
   - مشکل در build.gradle
   - مشکل network

### راه‌حل‌های رایج:
- مطمئن شو همه فایل‌ها آپلود شدن
- اگه مشکل داشت، Simple Build رو امتحان کن
- Issue جدید بساز و مشکل رو شرح بده

## 📱 **نصب APK:**

### روی گوشی Android:
1. APK رو به گوشی منتقل کن
2. Settings > Security > Unknown Sources فعال کن
3. روی APK کلیک کن
4. Install کن
5. بازی آماده!

### کنترل‌های بازی:
- **لمس و کشیدن**: حرکت بازیکن
- **برخورد با توپ**: ضربه زدن
- **هدف**: گل زدن!

## 🎉 **مزایای GitHub Actions:**

✅ **رایگان**: تا 2000 دقیقه در ماه
✅ **خودکار**: هر بار که کد تغییر کنی، APK جدید می‌سازه  
✅ **آسان**: نیازی به نصب چیزی نیست
✅ **قابل اعتماد**: سرورهای قدرتمند Google
✅ **سریع**: 5-10 دقیقه تا APK آماده بشه

## 🔗 **لینک‌های مفید:**

- [GitHub](https://github.com)
- [GitHub Actions مستندات](https://docs.github.com/en/actions)
- [Android Developer](https://developer.android.com)

---

## 💡 **نکات مهم:**

1. **اولین بار**: ممکنه کمی طول بکشه
2. **Updates**: هر بار کد تغییر کنی، APK جدید می‌سازه
3. **Artifacts**: APK ها 90 روز نگه داری می‌شن
4. **Multiple Builds**: می‌تونی هم‌زمان چند نسخه بسازی

**موفق باشی! 🎮⚽**