import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class Histogram extends JPanel {
    private BufferedImage image;
    private int[] histogram;

    public Histogram(BufferedImage image) {
        this.image = image;
        this.histogram = new int[256];
        calculateHistogram();
    }

    private void calculateHistogram() {
        int width = image.getWidth();
        int height = image.getHeight();

        // Вычисляем гистограмму
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Color c = new Color(image.getRGB(i, j));
                int intensity = (c.getRed() + c.getGreen() + c.getBlue()) / 3;
                histogram[intensity]++;
            }
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        int width = getWidth();
        int height = getHeight();
        int binWidth = width / histogram.length;

        // Рисуем гистограмму
        for (int i = 0; i < histogram.length; i++) {
            int binHeight = histogram[i] * height / getMaxCount();
            g.fillRect(i * binWidth, height - binHeight, binWidth, binHeight);
        }
    }

    private int getMaxCount() {
        int max = 0;
        for (int count : histogram) {
            max = Math.max(max, count);
        }
        return max;
    }
}
