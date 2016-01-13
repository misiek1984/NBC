using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using SampleDataCreator.Properties;

namespace SampleDataCreator
{
    public partial class Options : Form
    {
        #region Constans

        public const int DefaultPointSize = 5;
        public const int DefaultTranslateTransformStep = 3;
        public const float DefaultScaleTransformStep = 0.1f;
        public const string DefaultFormat = "{0}^{1}";
        public const string DefaultSeperator = "^";
        public const int DefaultCoordinatesScale = 1;

        #endregion

        #region Public Properties

        public int PointSize
        {
            get { return Settings.Default.PointSize; }
            private set { Settings.Default.PointSize = value; }
        }

        public int TranslateTransformStep
        {
            get { return Settings.Default.TranslateTransformStep; }
            private set { Settings.Default.TranslateTransformStep = value; }
        }

        public float ScaleTransformStep
        {
            get { return Settings.Default.ScaleTransformStep; }
            private set { Settings.Default.ScaleTransformStep = value; }
        }

        public int CoordinatesScale
        {
            get { return Settings.Default.CoordinatesScale; }
            private set { Settings.Default.CoordinatesScale = value; }
        }

        public string Format
        {
            get { return Settings.Default.Format; }
            private set { Settings.Default.Format = value; }
        }

        public string Seperator
        {
            get { return Settings.Default.Seperator; }
            private set { Settings.Default.Seperator = value; }
        }

        #endregion

        #region Constructor

        public Options()
        {
            InitializeComponent();

            SetControlsAccordingToSettings();
        }

        #endregion

        #region Private Methods

        private void SetControlsAccordingToSettings()
        {
            pointSizeTrackBar.Value = PointSize;
            pointSizeValue.Text = PointSize.ToString();
            stepTrackBar.Value = TranslateTransformStep;
            stepValue.Text = TranslateTransformStep.ToString();
            formatTextBox.Text = Format;
            seperatorTextBox.Text = Seperator;
            coordinatesScaleTexBox.Text = CoordinatesScale.ToString();
        }

        private void SetSettingsAccordingToContols()
        {
            Settings.Default.PointSize = pointSizeTrackBar.Value;
            Settings.Default.TranslateTransformStep = stepTrackBar.Value;
            Settings.Default.Format = formatTextBox.Text;
            Settings.Default.Seperator = seperatorTextBox.Text;

            int i;
            if(Int32.TryParse(coordinatesScaleTexBox.Text, out i))
                Settings.Default.CoordinatesScale = i;

            Settings.Default.Save();
        }

        private void SetDefault()
        {
            PointSize = DefaultPointSize;
            TranslateTransformStep = DefaultTranslateTransformStep;
            ScaleTransformStep = DefaultScaleTransformStep;
            Format = DefaultFormat;
            Seperator = DefaultSeperator;
            CoordinatesScale = DefaultCoordinatesScale;

            Settings.Default.Save();

            SetControlsAccordingToSettings();
        }

        #endregion

        #region Event Handlers

        private void ok_Click(object sender, EventArgs e)
        {
            SetSettingsAccordingToContols();

            DialogResult = DialogResult.OK;
            Hide();
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Hide();
        }

        private void defaultSettings_Click(object sender, EventArgs e)
        {
            SetDefault();
        }

        private void pointSize_ValueChanged(object sender, EventArgs e)
        {
            pointSizeValue.Text = pointSizeTrackBar.Value.ToString();
        }

        private void stepTrackBar_ValueChanged(object sender, EventArgs e)
        {
            stepValue.Text = stepTrackBar.Value.ToString();
        }

        #endregion
    }
}
