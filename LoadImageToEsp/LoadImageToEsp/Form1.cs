using System;
using System.Drawing;
using System.Net;
using System.Windows.Forms;

namespace LoadImageToEsp
{
    public partial class Form1 : Form
    {
        static Bitmap bmp = new Bitmap(12, 12);
        string path = "";

        public Form1()
        {
            InitializeComponent();
        }
        private void Button1_Click(object sender, EventArgs e)
        {
            try
            {
                if(path == null)
                {
                    MessageBox.Show("Изображение не загружено.");
                    return;
                }
                string str = "";
                path = path.Replace("\"", "");
                bmp = new Bitmap(path);
                bmp = new Bitmap(bmp, 12, 12);
                int k = 0;
                for (int i = 0; i < 12; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        str = str + bmp.GetPixel(i, j).R + " ";
                        str = str + bmp.GetPixel(i, j).G + " ";
                        str = str + bmp.GetPixel(i, j).B + " ";
                        k += 3;
                    }
                }
                HttpWebRequest req = (HttpWebRequest)WebRequest.Create(textBox1.Text + "?str=" + str);
                req.GetResponse();

                MessageBox.Show("Изображение отправлено!");
            }
            catch (Exception ex) { /*MessageBox.Show("Произошла ошибка: " + ex);*/ }
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Файлы изображений (*.bmp, *.jpg, *.png)|*.bmp;*.jpg;*.png";
            if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;
            path = openFileDialog1.FileName;
            bmp = new Bitmap(path);
            bmp = new Bitmap(bmp, 12, 12);
            Bitmap tobox = new Bitmap(240, 240);
            for (int y = 0; y < 12; y++)
            {
                for (int x = 0; x < 12; x++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        for (int i = 0; i < 20; i++)
                        {
                            tobox.SetPixel(20 * x + i, 20 * y + j, bmp.GetPixel(x, y));
                        }
                    }
                }
            }
            pictureBox1.Image = tobox;
        }
    }
}
