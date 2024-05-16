import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        try {
            // Загрузка изображения
            BufferedImage originalImage = ImageIO.read(new File("histogramEqualizationImage.jpg"));

            // Применение алгоритма линейного контраста
            BufferedImage linearContrastImage = ContrastEnhancement.linearContrast(originalImage);
            ImageIO.write(linearContrastImage, "jpg", new File("linearContrastImage.jpg"));

            // Применение алгоритма гистограммного выравнивания
            BufferedImage histogramEqualizationImage = ContrastEnhancement.histogramEqualization(originalImage);
            ImageIO.write(histogramEqualizationImage, "jpg", new File("histogramEqualizationImage.jpg"));

            System.out.println("Контрастность изображений успешно повышена!");
            // Создание экземпляра класса ImageContrast
            ImageContrast imageContrast = new ImageContrast(originalImage);

            Histogram histogram = new Histogram(originalImage);
            JFrame frame = new JFrame();
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.getContentPane().add(histogram);
            frame.setSize(400, 300);
            frame.setVisible(true);
        } catch (IOException e) {
            System.out.println("Произошла ошибка при обработке изображения");
            e.printStackTrace();
        }
    }
}
