using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Text.RegularExpressions;
using System.Reflection;

namespace SampleDataCreator
{
    public partial class Main : Form
    {
        #region Private Fields

        private Options _options = new Options();

        private List<PointF> _points = new List<PointF>();
        private List<int> _clusters = new List<int>();
        private List<Brush> _brushes = new List<Brush>();

        private int _offsetX = 0;
        private int _offsetY = 0;
        private float _scale = 1;

        private int _mouseX;
        private int _mouseY;

        #endregion

        #region Constructor

        public Main()
        {
            InitializeComponent();

            //Type t = typeof(Brushes);
            //foreach (PropertyInfo p in t.GetProperties(BindingFlags.Public | BindingFlags.Static))
            //{
            //    object value = p.GetValue(null, null);
            //    if (value is Brush)
            //    {
            //        _brushes.Add((Brush)value);
            //    }
            //}

            _brushes.Add(Brushes.Olive);
            _brushes.Add(Brushes.Black);
            _brushes.Add(Brushes.Green);
            _brushes.Add(Brushes.Yellow);
            _brushes.Add(Brushes.Blue);
            _brushes.Add(Brushes.Magenta);
            _brushes.Add(Brushes.Cyan);
            _brushes.Add(Brushes.Orange);
            _brushes.Add(Brushes.Violet);
            _brushes.Add(Brushes.Brown);
            _brushes.Add(Brushes.DarkBlue);
            _brushes.Add(Brushes.DeepPink);
            _brushes.Add(Brushes.Silver);
            _brushes.Add(Brushes.Indigo);
            _brushes.Add(Brushes.Salmon);
            _brushes.Add(Brushes.Sienna);
            _brushes.Add(Brushes.Thistle);
            _brushes.Add(Brushes.Turquoise);
            _brushes.Add(Brushes.YellowGreen);
            _brushes.Add(Brushes.Aquamarine);
            _brushes.Add(Brushes.Bisque);
            _brushes.Add(Brushes.CornflowerBlue);
            _brushes.Add(Brushes.DarkKhaki);
            _brushes.Add(Brushes.Firebrick);
            _brushes.Add(Brushes.Gainsboro);
            _brushes.Add(Brushes.Honeydew);
            _brushes.Add(Brushes.Ivory);
            _brushes.Add(Brushes.Lavender);
        }

        #endregion

        #region Private Methods

        private void OpenFile()
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                Clear();
                ResetPosition();

                string[] res = File.ReadAllLines(ofd.FileName);
                foreach (string s in res)
                {
                    string[] splitRes = s.Split(new String[] { _options.Seperator }, StringSplitOptions.RemoveEmptyEntries);
                    if (splitRes.Length == 2)
                    {
                        float x = 0;
                        float y = 0;

                        if (float.TryParse(splitRes[0], out x))
                        {
                            if (float.TryParse(splitRes[1], out y))
                            {
                                _points.Add(new PointF(x / _options.CoordinatesScale, y / _options.CoordinatesScale));
                            }
                        }
                    }
                }

                Invalidate(true);
            }
        }
        private void OpenResultFile()
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                _clusters.Clear();
                string[] res = File.ReadAllLines(ofd.FileName);
                foreach (string s in res)
                {
                    int cluster = -1;
                    if (Int32.TryParse(s, out cluster))
                        _clusters.Add(cluster + 1);
                    else
                        _clusters.Add(-1);
                }

                Invalidate(true);
            }
        }

        private void SaveToFile()
        {
            SaveFileDialog sfd = new SaveFileDialog();
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                StringBuilder sb = new StringBuilder();
                foreach (PointF p in _points)
                {
                    sb.AppendLine(String.Format(_options.Format, p.X, p.Y));
                }

                File.WriteAllText(sfd.FileName, sb.ToString());
            }
        }


        private void Clear()
        {
            _points.Clear();
            Invalidate(true);
        }
        private void ResetPosition()
        {
            _offsetX = 0;
            _offsetY = 0;
            _scale = 1;
            Invalidate(true);
        }
        private void ShowAll()
        {
        }

        #endregion

        #region Menu

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFile();
        }

        private void openResultsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenResultFile();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveToFile();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Clear();
        }


        private void resetPositionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ResetPosition();
        }

        private void goToToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (GoTo f = new GoTo())
            {
                if (f.ShowDialog() == DialogResult.OK)
                {
                    _offsetX = -(int)f.TargetPoint.Value.X;
                    _offsetY = -(int)f.TargetPoint.Value.Y;

                    Invalidate(true);
                }
            }
        }

        private void showAllToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void optionsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (_options.ShowDialog() == DialogResult.OK)
            {
                Invalidate(true);
            }
        }

        #endregion
        #region Painting

        private void Main_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

            Matrix t = new Matrix();
            t.Scale(1 / _scale, 1 / _scale);
            t.Translate(-_offsetX, -_offsetY);

            Point point = new Point(_mouseX, _mouseY);
            Point[] points = new Point[] { point };
            t.TransformPoints(points);

            g.DrawString(String.Format("{0}, {1}", points[0].X, points[0].Y), SystemFonts.DefaultFont, Brushes.Black, new Point(_mouseX + 6, _mouseY - 6));

            g.Transform = new Matrix();
            g.TranslateTransform(_offsetX, _offsetY );
            g.ScaleTransform(_scale, _scale);

            for (int i = 0; i < _points.Count; ++i)
            {
                PointF p = _points[i];

                if (_points.Count == _clusters.Count)
                {
                    int j = _clusters[i];
                    if (j > 0)     
                        e.Graphics.FillEllipse(_brushes[j % _brushes.Count], p.X, p.Y, _options.PointSize, _options.PointSize);
                    else
                        e.Graphics.FillEllipse(Brushes.Red, p.X, p.Y, _options.PointSize, _options.PointSize);
                }
                else
                {
                    e.Graphics.FillEllipse(Brushes.Red, p.X, p.Y, _options.PointSize, _options.PointSize);
                }
            }
        }

        private void Main_MouseClick(object sender, MouseEventArgs e)
        {
            Matrix m = new Matrix();
            m.Scale(1 / _scale, 1 / _scale);
            m.Translate(-_offsetX, -_offsetY);

            PointF[] array = new PointF[] { new Point(e.X, e.Y) };
            m.TransformPoints(array);
            _points.Add(new PointF() { X = array[0].X, Y = array[0].Y });
            Invalidate(true);
        }

        private void Main_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Up || e.KeyCode == Keys.W)
            {
                _offsetY += _options.TranslateTransformStep;
            }
            else if (e.KeyCode == Keys.Down || e.KeyCode == Keys.S)
            {
                _offsetY -= _options.TranslateTransformStep;
            }
            else if (e.KeyCode == Keys.Left || e.KeyCode == Keys.A)
            {
                _offsetX += _options.TranslateTransformStep;
            }
            else if (e.KeyCode == Keys.Right || e.KeyCode == Keys.D)
            {
                _offsetX -= _options.TranslateTransformStep;
            }
            else if (e.KeyCode == Keys.Q)
            {
                _scale += _options.ScaleTransformStep;
            }
            else if (e.KeyCode == Keys.E)
            {
                if (_scale > _options.ScaleTransformStep)
                 _scale -= _options.ScaleTransformStep;
            }

            Invalidate(true);
        }

        private void Main_MouseMove(object sender, MouseEventArgs e)
        {
            _mouseX = e.X;
            _mouseY = e.Y;
            Invalidate(true);
        }

        #endregion
    }
}
