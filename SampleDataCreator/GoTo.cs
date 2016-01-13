using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SampleDataCreator
{
    public partial class GoTo : Form
    {
        public PointF? TargetPoint
        {
            get 
            {
                float x;
                if (float.TryParse(xTextBox.Text, out x))
                {
                    float y;
                    if (float.TryParse(yTextBox.Text, out y))
                    {
                        return new PointF(x, y);
                    }
                }

                return null; 
            }
        }

        public GoTo()
        {
            InitializeComponent();
        }

        private void ok_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Hide();
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Hide();
        }
    }
}
