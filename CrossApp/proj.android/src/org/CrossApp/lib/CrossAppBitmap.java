
package org.CrossApp.lib;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.FontMetrics;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.text.BoringLayout;
import android.text.Layout;
import android.text.StaticLayout;
import android.text.TextPaint;
import android.text.TextUtils;
import android.util.Log;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public final class CrossAppBitmap {
    // ===========================================================
    // Constants
    // ===========================================================

    private static final int HORIZONTAL_ALIGN_LEFT = 1;
    private static final int HORIZONTAL_ALIGN_RIGHT = 2;
    private static final int HORIZONTAL_ALIGN_CENTER = 3;
    private static final int VERTICAL_ALIGN_TOP = 1;
    private static final int VERTICAL_ALIGN_BOTTOM = 2;
    private static final int VERTICAL_ALIGN_CENTER = 3;
    
    // ===========================================================
    // Fields
    // ===========================================================

    private static Context sContext;

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    public static void setContext(final Context context) {
        CrossAppBitmap.sContext = context;
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    // ===========================================================
    // Methods
    // ===========================================================

    private static native void nativeInitBitmapDC(final int width,
            final int height, final byte[] pixels);

    //http://egoco.de/post/19077604048/calculating-the-height-of-text-in-android
    public static int getTextHeight(String text, int maxWidth, float textSize, Typeface typeface) {
        TextPaint paint = new TextPaint(Paint.ANTI_ALIAS_FLAG | Paint.SUBPIXEL_TEXT_FLAG);
        paint.setTextSize(textSize);
        paint.setTypeface(typeface);

        int lineCount = 0;

        int index = 0;
        int length = text.length();

        while(index < length) {
            index += paint.breakText(text, index, length, true, maxWidth, null);
            lineCount++;
        }

        float actualHeight = (Math.abs(paint.ascent()) + Math.abs(paint.descent()));

        return (int)Math.floor(lineCount * actualHeight);
    }

    public static Typeface calculateShrinkTypeFace(String text, int width, int height, Layout.Alignment hAlignment, float textSize, TextPaint paint, boolean enableWrap)
    {
        if (width == 0 || height == 0) {
            return  paint.getTypeface();
        }
        float actualWidth = width + 1;
        float actualHeight = height + 1;
        float fontSize = textSize + 1;

        if (!enableWrap) {
            while (actualWidth > width || actualHeight > height) {
                fontSize = fontSize - 1;

                actualWidth = (int)Math.ceil( StaticLayout.getDesiredWidth(text, paint));
                actualHeight = getTextHeight(text, (int)actualWidth, fontSize, paint.getTypeface());

                paint.setTextSize(fontSize);
                if (fontSize <= 0) {
                    paint.setTextSize(textSize);
                    break;
                }
            }
        } else {
            while (actualHeight > height || actualWidth > width) {
                fontSize = fontSize - 1;

                Layout layout = new StaticLayout(text, paint, (int) width, hAlignment,1.0f,0.0f,false);
                actualWidth = layout.getWidth();
                actualHeight = layout.getLineTop(layout.getLineCount());

                paint.setTextSize(fontSize);

                if (fontSize <= 0) {
                    paint.setTextSize(textSize);
                    break;
                }
            }

        }
        return paint.getTypeface();
    }
    
    /**
     * 
     * @param string   
     * @param fontName 
     * @param fontSize    
     * @param fontTintR   		
     * @param fontTintG  
     * @param fontTintB   
     * @param fontTintA  
     * @param alignment 
     * @param width       
     * @param height      
     * @param shadow    
     * @param shadowDX  
     * @param shadowDY  
     * @param shadowBlur  
     * @param shadowOpacity  
     * @param stroke       
     * @param strokeR    
     * @param strokeG   
     * @param strokeB    
     * @param strokeA    
     * @param strokeSize  
     * @param bold
     * @param underLine
     * @param deleteLine
     * @param italics
     * @param italics_v
     * @param wordWrap
     * 
     * 
     * @return
     */
    public static boolean createTextBitmapShadowStroke(
    		String string,  
    		final String fontName, 
    		int fontSize,
            int fontTintR, int fontTintG, int fontTintB, int fontTintA,
            int alignment, 
            int width, 
            int height, 
            int shadow, float shadowDX, float shadowDY, float shadowBlur, float shadowOpacity, 
            int stroke, int strokeR, int strokeG, int strokeB, int strokeA, float strokeSize,
            int bold ,                                        
            int undeerLine, 
            int deleteLine , 
            int italics , 
            float italics_v , 
            int wordWrap
    		) 
    {
    	
        Layout.Alignment hAlignment = Layout.Alignment.ALIGN_NORMAL;
        int horizontalAlignment = alignment & 0x0F;
        switch (horizontalAlignment) {
            case HORIZONTAL_ALIGN_CENTER:
                hAlignment = Layout.Alignment.ALIGN_CENTER;
                break;
            case HORIZONTAL_ALIGN_RIGHT:
                hAlignment = Layout.Alignment.ALIGN_OPPOSITE;
                break;
            case HORIZONTAL_ALIGN_LEFT:
                break;
            default:
                break;
        }
        
        TextPaint paint = CrossAppBitmap.newPaint(fontName, fontSize);
        
        italics_v = -italics_v ; 
        paint.setFakeBoldText(bold > 0 ?true : false); //true为粗体，false为非粗体
        paint.setTextSkewX(italics > 0 ? italics_v : 0);     //float类型参数，负数表示右斜，整数左斜
        paint.setUnderlineText(undeerLine  >0 ? true : false); //true为下划线，false为非下划线
        paint.setStrikeThruText(deleteLine > 0 ? true: false); //true为删除线，false为非删除线
        
        int _increase =  italics > 0 ?  (int) ( fontSize * Math.abs(italics_v) * 0.5f ) : 0 ; 
        int _italics_trans = italics > 0 ? (   italics_v > 0 ?  _increase : -_increase  ) : 0 ; 
        
        if (stroke>0) {
            paint.setStyle(TextPaint.Style.STROKE);
            paint.setStrokeWidth(strokeSize);
        }
        
        int maxWidth = width;
        
        if (maxWidth <= 0) {
            maxWidth = (int)Math.ceil( StaticLayout.getDesiredWidth(string, paint));
        }

        Layout layout = null;
        int layoutWidth = 0;
        int layoutHeight = 0;
        
        layout = new StaticLayout(string, paint, maxWidth , hAlignment,1.0f,0.0f,false);

        layoutWidth = layout.getWidth();
        layoutHeight = layout.getLineTop(layout.getLineCount());

        int bitmapWidth = Math.max(layoutWidth, width);
        int bitmapHeight = layoutHeight;
        if (height > 0) {
            bitmapHeight = height;
        }
        
        if (bitmapWidth == 0 || bitmapHeight == 0) {
            return false;
        }
        
        int offsetX = 0;
        if (horizontalAlignment == HORIZONTAL_ALIGN_CENTER) {
            offsetX = (bitmapWidth - layoutWidth) / 2;
        }
        else if (horizontalAlignment == HORIZONTAL_ALIGN_RIGHT) {
            offsetX = bitmapWidth - layoutWidth;
        }
        offsetX += _italics_trans ; 
        
        int offsetY = 0;
        int verticalAlignment   = (alignment >> 4) & 0x0F;
        switch (verticalAlignment)
        {
            case VERTICAL_ALIGN_CENTER:
                offsetY = (bitmapHeight - layoutHeight) / 2;
                break;
            case VERTICAL_ALIGN_BOTTOM:
                offsetY = bitmapHeight - layoutHeight;
                break;
        }
        
        Bitmap bitmap = Bitmap.createBitmap((bitmapWidth + _increase) , bitmapHeight, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);
        canvas.translate(offsetX, offsetY);
        if ( stroke>0 )
        {
            paint.setARGB(strokeA, strokeR, strokeG, strokeB);
            layout.draw(canvas);
        }
        paint.setStyle(TextPaint.Style.FILL);
        paint.setARGB(fontTintA, fontTintR, fontTintG, fontTintB);
        layout.draw(canvas);
        
        CrossAppBitmap.initNativeObject(bitmap);
        return true;
    }
    
    
    

  public static float heightForFont(int fontSize)
  {
  
	  Paint p = new Paint();  
      p.setTextSize(fontSize);  
      FontMetrics fm = p.getFontMetrics();  
      
      int textHeight = (int) (Math.ceil(fm.descent - fm.ascent) + 2);  
	        
      return textHeight;
  }
  
  public static float heightForTextAtWidth(String string , int width , int fontsize)
  {	  
	  TextPaint paint = new TextPaint();
      paint.setTextSize(fontsize);
	  Layout layout = new StaticLayout(string, paint, width , Layout.Alignment.ALIGN_CENTER,1.0f,0.0f,false);
      	  
      return layout.getHeight();
  }
  
  public static float widthForTextAtOneLine(String string ,  int fontSize)
  {
      
	  TextPaint paint = new TextPaint();
      paint.setTextSize(fontSize);
      
      return paint.measureText(string) ; 
  }
  
    
    
    

    private static TextPaint newPaint(final String fontName, final int fontSize) {
        final TextPaint paint = new TextPaint();
        paint.setTextSize(fontSize);
        paint.setAntiAlias(true);

        // Set type face for paint, now it support .ttf file.
        if (fontName != null && fontName.endsWith(".ttf")) {
            try {
                final Typeface typeFace = CrossAppTypefaces.get(
                        CrossAppBitmap.sContext, fontName);
                paint.setTypeface(typeFace);
            } catch (final Exception e) {
                Log.e("Cocos2dxBitmap", "error to create ttf type face: "
                        + fontName);

                // The file may not find, use system font.
                paint.setTypeface(Typeface.create(fontName, Typeface.NORMAL));
            }
        } else {
            paint.setTypeface(Typeface.create(fontName, Typeface.NORMAL));
        }
        return paint;
    }
    
    private static void initNativeObject(final Bitmap bitmap) {
        final byte[] pixels = CrossAppBitmap.getPixels(bitmap);
        if (pixels == null) {
            return;
        }
        
        CrossAppBitmap.nativeInitBitmapDC(bitmap.getWidth(),
                bitmap.getHeight(), pixels);
    }

    private static byte[] getPixels(final Bitmap bitmap) {
        if (bitmap != null) {
            final byte[] pixels = new byte[bitmap.getWidth()
                    * bitmap.getHeight() * 4];
            final ByteBuffer buf = ByteBuffer.wrap(pixels);
            buf.order(ByteOrder.nativeOrder());
            bitmap.copyPixelsToBuffer(buf);
            return pixels;
        }

        return null;
    }

    public static int getFontSizeAccordingHeight(int height) {
        TextPaint paint = new TextPaint();
        Rect bounds = new Rect();

        paint.setTypeface(Typeface.DEFAULT);
        int text_size = 1;
        boolean found_desired_size = false;

        while (!found_desired_size) {
            paint.setTextSize(text_size);
            String text = "SghMNy";
            paint.getTextBounds(text, 0, text.length(), bounds);

            text_size++;

            if (height - bounds.height() <= 2) {
                found_desired_size = true;
            }
        }
        return text_size;
    }

    private static String getStringWithEllipsis(String string, float width, float fontSize) {
        if (TextUtils.isEmpty(string)) {
            return "";
        }

        TextPaint paint = new TextPaint();
        paint.setTypeface(Typeface.DEFAULT);
        paint.setTextSize(fontSize);

        return TextUtils.ellipsize(string, paint, width,
                TextUtils.TruncateAt.END).toString();
    }
}
