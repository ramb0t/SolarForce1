namespace iKlwa_Telemetry_System
{
    partial class UserInterface
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserInterface));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.lbl_avgSpeed = new System.Windows.Forms.Label();
            this.label31 = new System.Windows.Forms.Label();
            this.label30 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label15 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.taskbar_notification = new System.Windows.Forms.NotifyIcon(this.components);
            this.button3 = new System.Windows.Forms.Button();
            this.refresh_timer = new System.Windows.Forms.Timer(this.components);
            this.lbl_instSpeed = new System.Windows.Forms.Label();
            this.lbl_dist = new System.Windows.Forms.Label();
            this.lvl_PIn = new System.Windows.Forms.Label();
            this.lbl_POut = new System.Windows.Forms.Label();
            this.lbl_SoC = new System.Windows.Forms.Label();
            this.lbl_avgCellTemp = new System.Windows.Forms.Label();
            this.lbl_avgCellVoltage = new System.Windows.Forms.Label();
            this.lbl_HLim = new System.Windows.Forms.Label();
            this.lbl_LLim = new System.Windows.Forms.Label();
            this.lbl_BMSFault = new System.Windows.Forms.Label();
            this.lbl_MPPTFault = new System.Windows.Forms.Label();
            this.lbl_MPPTPIn1 = new System.Windows.Forms.Label();
            this.lbl_MPPTPIn3 = new System.Windows.Forms.Label();
            this.lbl_MPPTPIn2 = new System.Windows.Forms.Label();
            this.lbl_MPPTPIn4 = new System.Windows.Forms.Label();
            this.tabControl1.SuspendLayout();
            this.tabPage6.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tabPage5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.tabControl1.Controls.Add(this.tabPage6);
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Controls.Add(this.tabPage5);
            this.tabControl1.Location = new System.Drawing.Point(210, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(508, 406);
            this.tabControl1.TabIndex = 2;
            // 
            // tabPage6
            // 
            this.tabPage6.BackColor = System.Drawing.Color.Linen;
            this.tabPage6.Controls.Add(this.lbl_MPPTPIn4);
            this.tabPage6.Controls.Add(this.lbl_MPPTPIn2);
            this.tabPage6.Controls.Add(this.lbl_MPPTPIn3);
            this.tabPage6.Controls.Add(this.lbl_MPPTPIn1);
            this.tabPage6.Controls.Add(this.lbl_MPPTFault);
            this.tabPage6.Controls.Add(this.lbl_BMSFault);
            this.tabPage6.Controls.Add(this.lbl_LLim);
            this.tabPage6.Controls.Add(this.lbl_HLim);
            this.tabPage6.Controls.Add(this.lbl_avgCellVoltage);
            this.tabPage6.Controls.Add(this.lbl_avgCellTemp);
            this.tabPage6.Controls.Add(this.lbl_SoC);
            this.tabPage6.Controls.Add(this.lbl_POut);
            this.tabPage6.Controls.Add(this.lvl_PIn);
            this.tabPage6.Controls.Add(this.lbl_dist);
            this.tabPage6.Controls.Add(this.lbl_instSpeed);
            this.tabPage6.Controls.Add(this.lbl_avgSpeed);
            this.tabPage6.Controls.Add(this.label31);
            this.tabPage6.Controls.Add(this.label30);
            this.tabPage6.Controls.Add(this.label29);
            this.tabPage6.Controls.Add(this.label28);
            this.tabPage6.Controls.Add(this.label27);
            this.tabPage6.Controls.Add(this.label26);
            this.tabPage6.Controls.Add(this.label25);
            this.tabPage6.Controls.Add(this.label24);
            this.tabPage6.Controls.Add(this.label23);
            this.tabPage6.Controls.Add(this.label22);
            this.tabPage6.Controls.Add(this.label21);
            this.tabPage6.Controls.Add(this.label20);
            this.tabPage6.Controls.Add(this.label18);
            this.tabPage6.Controls.Add(this.label16);
            this.tabPage6.Controls.Add(this.label14);
            this.tabPage6.Controls.Add(this.label7);
            this.tabPage6.Location = new System.Drawing.Point(4, 25);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Size = new System.Drawing.Size(500, 377);
            this.tabPage6.TabIndex = 5;
            this.tabPage6.Text = "Summary";
            // 
            // lbl_avgSpeed
            // 
            this.lbl_avgSpeed.AutoSize = true;
            this.lbl_avgSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_avgSpeed.Location = new System.Drawing.Point(268, 17);
            this.lbl_avgSpeed.Name = "lbl_avgSpeed";
            this.lbl_avgSpeed.Size = new System.Drawing.Size(67, 25);
            this.lbl_avgSpeed.TabIndex = 26;
            this.lbl_avgSpeed.Text = "_____";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label31.Location = new System.Drawing.Point(268, 341);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(180, 25);
            this.label31.TabIndex = 25;
            this.label31.Text = "Power In (MPPT4):";
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label30.Location = new System.Drawing.Point(268, 316);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(180, 25);
            this.label30.TabIndex = 24;
            this.label30.Text = "Power In (MPPT2):";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label29.Location = new System.Drawing.Point(18, 341);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(180, 25);
            this.label29.TabIndex = 23;
            this.label29.Text = "Power In (MPPT3):";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label28.Location = new System.Drawing.Point(18, 316);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(180, 25);
            this.label28.TabIndex = 22;
            this.label28.Text = "Power In (MPPT1):";
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label27.Location = new System.Drawing.Point(18, 254);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(183, 25);
            this.label27.TabIndex = 21;
            this.label27.Text = "MPPT Fault Status:";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label26.Location = new System.Drawing.Point(18, 229);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(171, 25);
            this.label26.TabIndex = 20;
            this.label26.Text = "BMS Fault Status:";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label25.Location = new System.Drawing.Point(268, 283);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(65, 25);
            this.label25.TabIndex = 19;
            this.label25.Text = "HLIM:";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label24.Location = new System.Drawing.Point(18, 283);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(62, 25);
            this.label24.TabIndex = 18;
            this.label24.Text = "LLIM:";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label23.Location = new System.Drawing.Point(18, 167);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(248, 25);
            this.label23.TabIndex = 17;
            this.label23.Text = "Average Cell Temperature:";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label22.Location = new System.Drawing.Point(18, 192);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(203, 25);
            this.label22.TabIndex = 16;
            this.label22.Text = "Average Cell Voltage:";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label21.Location = new System.Drawing.Point(18, 142);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(58, 25);
            this.label21.TabIndex = 15;
            this.label21.Text = "SoC:";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label20.Location = new System.Drawing.Point(18, 117);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(110, 25);
            this.label20.TabIndex = 14;
            this.label20.Text = "Power Out:";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label18.Location = new System.Drawing.Point(18, 92);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(94, 25);
            this.label18.TabIndex = 13;
            this.label18.Text = "Power In:";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label16.Location = new System.Drawing.Point(18, 67);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(180, 25);
            this.label16.TabIndex = 12;
            this.label16.Text = "Distance Travelled:";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.Location = new System.Drawing.Point(18, 42);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(204, 25);
            this.label14.TabIndex = 11;
            this.label14.Text = "Instantaneous Speed:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(18, 17);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(155, 25);
            this.label7.TabIndex = 10;
            this.label7.Text = "Average Speed:";
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.tabPage1.Controls.Add(this.groupBox4);
            this.tabPage1.Controls.Add(this.groupBox3);
            this.tabPage1.Location = new System.Drawing.Point(4, 25);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(500, 377);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Solar Car Motion";
            // 
            // groupBox4
            // 
            this.groupBox4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.groupBox4.Controls.Add(this.label15);
            this.groupBox4.Controls.Add(this.label17);
            this.groupBox4.Controls.Add(this.label19);
            this.groupBox4.Location = new System.Drawing.Point(235, 22);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(196, 142);
            this.groupBox4.TabIndex = 7;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Sensor Status";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(17, 69);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(67, 13);
            this.label15.TabIndex = 4;
            this.label15.Text = "Gyro Module";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(17, 47);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(118, 13);
            this.label17.TabIndex = 2;
            this.label17.Text = "Hall Effect Sensor Rear";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(17, 25);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(119, 13);
            this.label19.TabIndex = 0;
            this.label19.Text = "Hall Effect Sensor Front";
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Location = new System.Drawing.Point(15, 22);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(191, 198);
            this.groupBox3.TabIndex = 6;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Sensor Data";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(105, 164);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(55, 13);
            this.label5.TabIndex = 11;
            this.label5.Text = "________";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(17, 164);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(82, 13);
            this.label6.TabIndex = 10;
            this.label6.Text = "Time Received:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(105, 106);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "________";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(17, 106);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(82, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Time Received:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(105, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "________";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Time Received:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(65, 142);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(55, 13);
            this.label8.TabIndex = 5;
            this.label8.Text = "________";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(17, 142);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 13);
            this.label9.TabIndex = 4;
            this.label9.Text = "Incline:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(92, 84);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(55, 13);
            this.label10.TabIndex = 3;
            this.label10.Text = "________";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(17, 84);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(69, 13);
            this.label11.TabIndex = 2;
            this.label11.Text = "Acceleration:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(65, 25);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(55, 13);
            this.label12.TabIndex = 1;
            this.label12.Text = "________";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(17, 25);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(41, 13);
            this.label13.TabIndex = 0;
            this.label13.Text = "Speed:";
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.tabPage2.Location = new System.Drawing.Point(4, 25);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(500, 400);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Solar Car Electrical";
            // 
            // tabPage3
            // 
            this.tabPage3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.tabPage3.Location = new System.Drawing.Point(4, 25);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(500, 400);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "RF Link";
            // 
            // tabPage4
            // 
            this.tabPage4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
            this.tabPage4.Location = new System.Drawing.Point(4, 25);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(500, 400);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Support Car System";
            // 
            // tabPage5
            // 
            this.tabPage5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.tabPage5.Controls.Add(this.zedGraphControl1);
            this.tabPage5.Location = new System.Drawing.Point(4, 25);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Size = new System.Drawing.Size(500, 400);
            this.tabPage5.TabIndex = 4;
            this.tabPage5.Text = "Graphs";
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.Location = new System.Drawing.Point(12, 11);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0D;
            this.zedGraphControl1.ScrollMaxX = 0D;
            this.zedGraphControl1.ScrollMaxY = 0D;
            this.zedGraphControl1.ScrollMaxY2 = 0D;
            this.zedGraphControl1.ScrollMinX = 0D;
            this.zedGraphControl1.ScrollMinY = 0D;
            this.zedGraphControl1.ScrollMinY2 = 0D;
            this.zedGraphControl1.Size = new System.Drawing.Size(473, 261);
            this.zedGraphControl1.TabIndex = 0;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::iKlwa_Telemetry_System.Properties.Resources.ukzn_logo;
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(192, 213);
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            // 
            // button1
            // 
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button1.Font = new System.Drawing.Font("Cooper Md BT", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.Location = new System.Drawing.Point(13, 232);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(191, 43);
            this.button1.TabIndex = 4;
            this.button1.Text = "Connect to Hardware";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button2.Font = new System.Drawing.Font("Cooper Md BT", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button2.Location = new System.Drawing.Point(12, 302);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(191, 43);
            this.button2.TabIndex = 5;
            this.button2.Text = "Generate Error Report";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // taskbar_notification
            // 
            this.taskbar_notification.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Warning;
            this.taskbar_notification.BalloonTipText = "The Solar Car Telemetry System has detected an error.";
            this.taskbar_notification.BalloonTipTitle = "Unread Telemetry Warning Messages";
            this.taskbar_notification.Icon = ((System.Drawing.Icon)(resources.GetObject("taskbar_notification.Icon")));
            this.taskbar_notification.Text = "Unread Warning Messages";
            // 
            // button3
            // 
            this.button3.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button3.Font = new System.Drawing.Font("Cooper Md BT", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button3.Location = new System.Drawing.Point(13, 370);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(191, 43);
            this.button3.TabIndex = 6;
            this.button3.Text = "No New Warnings";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // refresh_timer
            // 
            this.refresh_timer.Enabled = true;
            this.refresh_timer.Interval = 1000;
            this.refresh_timer.Tick += new System.EventHandler(this.refresh_timer_Tick);
            // 
            // lbl_instSpeed
            // 
            this.lbl_instSpeed.AutoSize = true;
            this.lbl_instSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_instSpeed.Location = new System.Drawing.Point(268, 42);
            this.lbl_instSpeed.Name = "lbl_instSpeed";
            this.lbl_instSpeed.Size = new System.Drawing.Size(67, 25);
            this.lbl_instSpeed.TabIndex = 27;
            this.lbl_instSpeed.Text = "_____";
            // 
            // lbl_dist
            // 
            this.lbl_dist.AutoSize = true;
            this.lbl_dist.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_dist.Location = new System.Drawing.Point(268, 67);
            this.lbl_dist.Name = "lbl_dist";
            this.lbl_dist.Size = new System.Drawing.Size(67, 25);
            this.lbl_dist.TabIndex = 28;
            this.lbl_dist.Text = "_____";
            // 
            // lvl_PIn
            // 
            this.lvl_PIn.AutoSize = true;
            this.lvl_PIn.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lvl_PIn.Location = new System.Drawing.Point(268, 92);
            this.lvl_PIn.Name = "lvl_PIn";
            this.lvl_PIn.Size = new System.Drawing.Size(67, 25);
            this.lvl_PIn.TabIndex = 29;
            this.lvl_PIn.Text = "_____";
            // 
            // lbl_POut
            // 
            this.lbl_POut.AutoSize = true;
            this.lbl_POut.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_POut.Location = new System.Drawing.Point(268, 117);
            this.lbl_POut.Name = "lbl_POut";
            this.lbl_POut.Size = new System.Drawing.Size(67, 25);
            this.lbl_POut.TabIndex = 30;
            this.lbl_POut.Text = "_____";
            // 
            // lbl_SoC
            // 
            this.lbl_SoC.AutoSize = true;
            this.lbl_SoC.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_SoC.Location = new System.Drawing.Point(268, 142);
            this.lbl_SoC.Name = "lbl_SoC";
            this.lbl_SoC.Size = new System.Drawing.Size(67, 25);
            this.lbl_SoC.TabIndex = 31;
            this.lbl_SoC.Text = "_____";
            // 
            // lbl_avgCellTemp
            // 
            this.lbl_avgCellTemp.AutoSize = true;
            this.lbl_avgCellTemp.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_avgCellTemp.Location = new System.Drawing.Point(268, 167);
            this.lbl_avgCellTemp.Name = "lbl_avgCellTemp";
            this.lbl_avgCellTemp.Size = new System.Drawing.Size(67, 25);
            this.lbl_avgCellTemp.TabIndex = 32;
            this.lbl_avgCellTemp.Text = "_____";
            // 
            // lbl_avgCellVoltage
            // 
            this.lbl_avgCellVoltage.AutoSize = true;
            this.lbl_avgCellVoltage.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_avgCellVoltage.Location = new System.Drawing.Point(268, 192);
            this.lbl_avgCellVoltage.Name = "lbl_avgCellVoltage";
            this.lbl_avgCellVoltage.Size = new System.Drawing.Size(67, 25);
            this.lbl_avgCellVoltage.TabIndex = 33;
            this.lbl_avgCellVoltage.Text = "_____";
            // 
            // lbl_HLim
            // 
            this.lbl_HLim.AutoSize = true;
            this.lbl_HLim.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_HLim.Location = new System.Drawing.Point(339, 283);
            this.lbl_HLim.Name = "lbl_HLim";
            this.lbl_HLim.Size = new System.Drawing.Size(67, 25);
            this.lbl_HLim.TabIndex = 34;
            this.lbl_HLim.Text = "_____";
            // 
            // lbl_LLim
            // 
            this.lbl_LLim.AutoSize = true;
            this.lbl_LLim.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_LLim.Location = new System.Drawing.Point(268, 229);
            this.lbl_LLim.Name = "lbl_LLim";
            this.lbl_LLim.Size = new System.Drawing.Size(67, 25);
            this.lbl_LLim.TabIndex = 35;
            this.lbl_LLim.Text = "_____";
            // 
            // lbl_BMSFault
            // 
            this.lbl_BMSFault.AutoSize = true;
            this.lbl_BMSFault.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_BMSFault.Location = new System.Drawing.Point(86, 283);
            this.lbl_BMSFault.Name = "lbl_BMSFault";
            this.lbl_BMSFault.Size = new System.Drawing.Size(67, 25);
            this.lbl_BMSFault.TabIndex = 36;
            this.lbl_BMSFault.Text = "_____";
            // 
            // lbl_MPPTFault
            // 
            this.lbl_MPPTFault.AutoSize = true;
            this.lbl_MPPTFault.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_MPPTFault.Location = new System.Drawing.Point(268, 254);
            this.lbl_MPPTFault.Name = "lbl_MPPTFault";
            this.lbl_MPPTFault.Size = new System.Drawing.Size(67, 25);
            this.lbl_MPPTFault.TabIndex = 37;
            this.lbl_MPPTFault.Text = "_____";
            // 
            // lbl_MPPTPIn1
            // 
            this.lbl_MPPTPIn1.AutoSize = true;
            this.lbl_MPPTPIn1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_MPPTPIn1.Location = new System.Drawing.Point(195, 316);
            this.lbl_MPPTPIn1.Name = "lbl_MPPTPIn1";
            this.lbl_MPPTPIn1.Size = new System.Drawing.Size(67, 25);
            this.lbl_MPPTPIn1.TabIndex = 38;
            this.lbl_MPPTPIn1.Text = "_____";
            // 
            // lbl_MPPTPIn3
            // 
            this.lbl_MPPTPIn3.AutoSize = true;
            this.lbl_MPPTPIn3.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_MPPTPIn3.Location = new System.Drawing.Point(195, 341);
            this.lbl_MPPTPIn3.Name = "lbl_MPPTPIn3";
            this.lbl_MPPTPIn3.Size = new System.Drawing.Size(67, 25);
            this.lbl_MPPTPIn3.TabIndex = 39;
            this.lbl_MPPTPIn3.Text = "_____";
            // 
            // lbl_MPPTPIn2
            // 
            this.lbl_MPPTPIn2.AutoSize = true;
            this.lbl_MPPTPIn2.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_MPPTPIn2.Location = new System.Drawing.Point(450, 316);
            this.lbl_MPPTPIn2.Name = "lbl_MPPTPIn2";
            this.lbl_MPPTPIn2.Size = new System.Drawing.Size(45, 25);
            this.lbl_MPPTPIn2.TabIndex = 40;
            this.lbl_MPPTPIn2.Text = "___";
            // 
            // lbl_MPPTPIn4
            // 
            this.lbl_MPPTPIn4.AutoSize = true;
            this.lbl_MPPTPIn4.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_MPPTPIn4.Location = new System.Drawing.Point(450, 341);
            this.lbl_MPPTPIn4.Name = "lbl_MPPTPIn4";
            this.lbl_MPPTPIn4.Size = new System.Drawing.Size(45, 25);
            this.lbl_MPPTPIn4.TabIndex = 41;
            this.lbl_MPPTPIn4.Text = "___";
            // 
            // UserInterface
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(726, 425);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "UserInterface";
            this.Text = "UKZN Solar Car Telemetry System";
            this.TransparencyKey = System.Drawing.Color.Maroon;
            this.tabControl1.ResumeLayout(false);
            this.tabPage6.ResumeLayout(false);
            this.tabPage6.PerformLayout();
            this.tabPage1.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.tabPage5.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.TabPage tabPage5;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NotifyIcon taskbar_notification;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Timer refresh_timer;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.Label lbl_avgSpeed;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label lbl_instSpeed;
        private System.Windows.Forms.Label lbl_MPPTPIn4;
        private System.Windows.Forms.Label lbl_MPPTPIn2;
        private System.Windows.Forms.Label lbl_MPPTPIn3;
        private System.Windows.Forms.Label lbl_MPPTPIn1;
        private System.Windows.Forms.Label lbl_MPPTFault;
        private System.Windows.Forms.Label lbl_BMSFault;
        private System.Windows.Forms.Label lbl_LLim;
        private System.Windows.Forms.Label lbl_HLim;
        private System.Windows.Forms.Label lbl_avgCellVoltage;
        private System.Windows.Forms.Label lbl_avgCellTemp;
        private System.Windows.Forms.Label lbl_SoC;
        private System.Windows.Forms.Label lbl_POut;
        private System.Windows.Forms.Label lvl_PIn;
        private System.Windows.Forms.Label lbl_dist;

    }
}