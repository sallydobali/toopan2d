# Add project specific ProGuard rules here.
# You can control the set of applied configuration files using the
# proguardFiles setting in build.gradle.

-keep class com.toopan2d.game.** { *; }

# Keep native methods
-keepclasseswithmembernames class * {
    native <methods>;
}