namespace SampleDataCreator
{
    partial class Options
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pointSizeTrackBar = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.cancel = new System.Windows.Forms.Button();
            this.ok = new System.Windows.Forms.Button();
            this.pointSizeValue = new System.Windows.Forms.TextBox();
            this.stepValue = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.stepTrackBar = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            this.formatTextBox = new System.Windows.Forms.TextBox();
            this.defaultSettings = new System.Windows.Forms.Button();
            this.seperatorTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.coordinatesScaleTexBox = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pointSizeTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.stepTrackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // pointSizeTrackBar
            // 
            this.pointSizeTrackBar.LargeChange = 1;
            this.pointSizeTrackBar.Location = new System.Drawing.Point(85, 9);
            this.pointSizeTrackBar.Maximum = 20;
            this.pointSizeTrackBar.Minimum = 1;
            this.pointSizeTrackBar.Name = "pointSizeTrackBar";
            this.pointSizeTrackBar.Size = new System.Drawing.Size(227, 45);
            this.pointSizeTrackBar.TabIndex = 0;
            this.pointSizeTrackBar.Value = 5;
            this.pointSizeTrackBar.ValueChanged += new System.EventHandler(this.pointSize_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Point size";
            // 
            // cancel
            // 
            this.cancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cancel.Location = new System.Drawing.Point(93, 245);
            this.cancel.Name = "cancel";
            this.cancel.Size = new System.Drawing.Size(75, 23);
            this.cancel.TabIndex = 2;
            this.cancel.Text = "Cancel";
            this.cancel.UseVisualStyleBackColor = true;
            this.cancel.Click += new System.EventHandler(this.cancel_Click);
            // 
            // ok
            // 
            this.ok.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.ok.Location = new System.Drawing.Point(12, 245);
            this.ok.Name = "ok";
            this.ok.Size = new System.Drawing.Size(75, 23);
            this.ok.TabIndex = 3;
            this.ok.Text = "OK";
            this.ok.UseVisualStyleBackColor = true;
            this.ok.Click += new System.EventHandler(this.ok_Click);
            // 
            // pointSizeValue
            // 
            this.pointSizeValue.Enabled = false;
            this.pointSizeValue.Location = new System.Drawing.Point(318, 16);
            this.pointSizeValue.Name = "pointSizeValue";
            this.pointSizeValue.Size = new System.Drawing.Size(43, 20);
            this.pointSizeValue.TabIndex = 4;
            // 
            // stepValue
            // 
            this.stepValue.Enabled = false;
            this.stepValue.Location = new System.Drawing.Point(318, 67);
            this.stepValue.Name = "stepValue";
            this.stepValue.Size = new System.Drawing.Size(43, 20);
            this.stepValue.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(74, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Translate step";
            // 
            // stepTrackBar
            // 
            this.stepTrackBar.LargeChange = 1;
            this.stepTrackBar.Location = new System.Drawing.Point(85, 60);
            this.stepTrackBar.Maximum = 20;
            this.stepTrackBar.Minimum = 1;
            this.stepTrackBar.Name = "stepTrackBar";
            this.stepTrackBar.Size = new System.Drawing.Size(227, 45);
            this.stepTrackBar.TabIndex = 5;
            this.stepTrackBar.Value = 3;
            this.stepTrackBar.ValueChanged += new System.EventHandler(this.stepTrackBar_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 140);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Format";
            // 
            // formatTextBox
            // 
            this.formatTextBox.Location = new System.Drawing.Point(54, 133);
            this.formatTextBox.Name = "formatTextBox";
            this.formatTextBox.Size = new System.Drawing.Size(219, 20);
            this.formatTextBox.TabIndex = 9;
            // 
            // defaultSettings
            // 
            this.defaultSettings.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.defaultSettings.Location = new System.Drawing.Point(174, 245);
            this.defaultSettings.Name = "defaultSettings";
            this.defaultSettings.Size = new System.Drawing.Size(75, 23);
            this.defaultSettings.TabIndex = 10;
            this.defaultSettings.Text = "Default";
            this.defaultSettings.UseVisualStyleBackColor = true;
            this.defaultSettings.Click += new System.EventHandler(this.defaultSettings_Click);
            // 
            // seperatorTextBox
            // 
            this.seperatorTextBox.Location = new System.Drawing.Point(71, 155);
            this.seperatorTextBox.Name = "seperatorTextBox";
            this.seperatorTextBox.Size = new System.Drawing.Size(43, 20);
            this.seperatorTextBox.TabIndex = 12;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 162);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Seperator";
            // 
            // coordinatesScaleTexBox
            // 
            this.coordinatesScaleTexBox.Location = new System.Drawing.Point(109, 107);
            this.coordinatesScaleTexBox.Name = "coordinatesScaleTexBox";
            this.coordinatesScaleTexBox.Size = new System.Drawing.Size(95, 20);
            this.coordinatesScaleTexBox.TabIndex = 13;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 114);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(91, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "Coordinates scale";
            // 
            // Options
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(398, 278);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.coordinatesScaleTexBox);
            this.Controls.Add(this.seperatorTextBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.defaultSettings);
            this.Controls.Add(this.formatTextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.stepValue);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.stepTrackBar);
            this.Controls.Add(this.pointSizeValue);
            this.Controls.Add(this.ok);
            this.Controls.Add(this.cancel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pointSizeTrackBar);
            this.Name = "Options";
            this.Text = "Options";
            ((System.ComponentModel.ISupportInitialize)(this.pointSizeTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.stepTrackBar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TrackBar pointSizeTrackBar;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button cancel;
        private System.Windows.Forms.Button ok;
        private System.Windows.Forms.TextBox pointSizeValue;
        private System.Windows.Forms.TextBox stepValue;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TrackBar stepTrackBar;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox formatTextBox;
        private System.Windows.Forms.Button defaultSettings;
        private System.Windows.Forms.TextBox seperatorTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox coordinatesScaleTexBox;
        private System.Windows.Forms.Label label5;
    }
}