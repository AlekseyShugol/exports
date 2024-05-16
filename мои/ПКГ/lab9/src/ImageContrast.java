import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class ImageContrast {
    private BufferedImage image;

    public ImageContrast(BufferedImage image) {
        this.image = image;
    }

    public BufferedImage linearStretching() {
        int width = image.getWidth();
        int height = image.getHeight();
        int min = 255;
        int max = 0;

        // Находим минимальное и максимальное значения интенсивности
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Color c = new Color(image.getRGB(i, j));
                int intensity = (c.getRed() + c.getGreen() + c.getBlue()) / 3;
                min = Math.min(min, intensity);
                max = Math.max(max, intensity);
            }
        }

        BufferedImage result = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

        // Применяем линейное растяжение
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Color c = new Color(image.getRGB(i, j));
                int red = 255 * (c.getRed() - min) / (max - min);
                int green = 255 * (c.getGreen() - min) / (max - min);
                int blue = 255 * (c.getBlue() - min) / (max - min);

                // Проверяем, что значения цвета находятся в допустимом диапазоне
                red = Math.max(0, Math.min(255, red));
                green = Math.max(0, Math.min(255, green));
                blue = Math.max(0, Math.min(255, blue));

                result.setRGB(i, j, new Color(red, green, blue).getRGB());
            }
        }

        return result;
    }


    public BufferedImage histogramEqualization() {
        int width = image.getWidth();
        int height = image.getHeight();
        int[] histogram = new int[256];
        int totalPixels = width * height;

        // Вычисляем гистограмму
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Color c = new Color(image.getRGB(i, j));
                int intensity = (c.getRed() + c.getGreen() + c.getBlue()) / 3;
                histogram[intensity]++;
            }
        }

        // Вычисляем кумулятивную гистограмму
        int[] cumulativeHistogram = new int[256];
        cumulativeHistogram[0] = histogram[0];
        for (int i = 1; i < 256; i++) {
            cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogram[i];
        }

        BufferedImage result = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

        // Применяем эквализацию гистограммы
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Color c = new Color(image.getRGB(i, j));
                int red = 255 * cumulativeHistogram[c.getRed()] / totalPixels;
                int green = 255 * cumulativeHistogram[c.getGreen()] / totalPixels;
                int blue = 255 * cumulativeHistogram[c.getBlue()] / totalPixels;
                result.setRGB(i, j, new Color(red, green, blue).getRGB());
            }
        }

        return result;
    }
}
