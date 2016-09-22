using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Test
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void buttonRect_Click(object sender, EventArgs e)
        {
            string str = string.Format("<rect x=\"{0}\" y=\"{1}\" width=\"{2}\" height=\"{3}\"/>",
                textBoxRectX.Text, textBoxRectY.Text, textBoxRectWidth.Text, textBoxRectHeight.Text);
            textBoxCode.Text += "\r\n" + str + "\r\n";
        }

        private void buttonCircle_Click(object sender, EventArgs e)
        {
            string str = string.Format("<circle cx =\"{0}\" cy=\"{1}\" r=\"{2}\"/>",
                textBoxCircleCx.Text, textBoxCircleCy.Text, textBoxCircleR.Text);
            textBoxCode.Text += "\r\n" + str + "\r\n";
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            using (FileStream fs = File.Create("text.svg"))
            {
                using (StreamWriter sw = new StreamWriter(fs))
                {
                    sw.WriteLine("<?xml version=\"1.0\" standalone=\"no\"?>");
                    sw.WriteLine("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">");
                    sw.WriteLine("<svg width=\"100%\" height=\"100%\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">");
                    sw.Write(textBoxCode.Text);
                    sw.WriteLine("</svg>");
                }
            }
        }
    }
}
