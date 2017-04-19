using ARadarUI;
using ARadarUI.Pages;
using Microsoft.Graphics.Canvas;
using Microsoft.Graphics.Canvas.Brushes;
using Microsoft.Graphics.Canvas.Text;
using Microsoft.Graphics.Canvas.UI.Xaml;
using Microsoft.Graphics.Canvas.Effects;
using System.Threading.Tasks;

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Microsoft.Graphics.Canvas.Geometry;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace ARadarUI
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        // Visuals
        private CanvasDrawingSession ds;
        private Vector2 origin;
        private float w = 900, h = 900;
        private double radius = 0;
        private int SCR_MARGIN = 80;
        private float font_scale = 1;
        // Visuals Colors
        private Color SCOPE_PEN_COLOR = Colors.GreenYellow;
        private Color SCOPE_TEXT_COLOR = Colors.DeepSkyBlue;
        private Color SCOPE_TEXT_HEADER_COLOR = Colors.Firebrick;

        // Radar Variables
        private bool chkRingsValue = false, chkHeadLineValue = true;
        private bool VRM1_STATE, VRM2_STATE, BRG1_STATE, BRG2_STATE;
        private float SelectedRange = 6f, SelectedRing = 6f, RingInterval = 1f;
        private float VRM1 = 0, VRM2 = 0, COURSE = 30;
        private int BRG1 = 0, BRG2 = 0, BRG1HK = 0, BRG2HK = 0;
        private object[] ranges = { 0.25f, 0.75f, 1.5f, 3f, 6f, 8f, 12f, 24f, 48f, 64f, 96f };
        private object[] rings = { 0, 2, 4, 6, 8, 10, 12 };
        private DisplayMode RadarDisplay = DisplayMode.COURSE_UP;

        // Begin of MATH HELPER FUNCTIONS
        Random rnd = new Random();
        private byte RndByte() { return (byte)rnd.Next(256); }
        private float RndX() { return (float)(rnd.NextDouble() * canViewPort.ActualWidth); }
        private float RndY() { return (float)(rnd.NextDouble() * canViewPort.ActualHeight); }
        private float[] LineCoord(int angleIn, float radius, float center)
        {
            float[] coord = new float[2]; // Setting up the int array for return
            angleIn %= 360;
            angleIn *= 1;

            if (angleIn >= 0 && angleIn <= 180)
            {
                coord[0] = center + (float)(radius * Math.Sin(Math.PI * angleIn / 180));
                coord[1] = center - (float)(radius * Math.Cos(Math.PI * angleIn / 180));
            }
            else
            {
                coord[0] = center - (float)(radius * -Math.Sin(Math.PI * angleIn / 180));
                coord[1] = center - (float)(radius * Math.Cos(Math.PI * angleIn / 180));
            }
            return coord;
        }
        private float[] LineCoord(int angleIn, float radius, Vector2 center)
        {
            if (h < w)
                return LineCoord(angleIn, radius, center.Y);
            else
                return LineCoord(angleIn, radius, center.X);
        }
        private void CalcBRG1HK(float brg1)
        {
            if (brg1 >= 0)
                BRG1HK = (int)Math.Round(((COURSE + brg1) % 360), 0);
            else
                BRG1HK = (int)Math.Round((COURSE + (float)(360 + brg1)) % 360, 0);

            if(RadarDisplay == DisplayMode.COURSE_UP)
            {
                if(brg1>=0)
                    BRG1HK = (int)Math.Round( brg1 , 0);
                else
                    BRG1HK = (int)Math.Round(360 + brg1, 0);
            }

            //Refresh BRG1 text
            txtBRG1.Text = BRG1HK.ToString("000") + "°";
        }
        private void CalcBRG2HK(float brg2)
        {
            if (brg2 >= 0)
                BRG2HK = (int)Math.Round(((COURSE + brg2) % 360), 0);
            else
                BRG2HK = (int)Math.Round((COURSE + (float)(360 + brg2)) % 360, 0);

            if (RadarDisplay == DisplayMode.COURSE_UP)
            {
                if (brg2 >= 0)
                    BRG2HK = (int)Math.Round(brg2, 0);
                else
                    BRG2HK = (int)Math.Round(360 + brg2, 0);
            }
            //Refresh BRG2 text
            txtBRG2.Text = BRG2HK.ToString("000") + "°";
        }
        // End of MATH HELPER FUNCTIONS

        public MainPage()
        {
            this.InitializeComponent();
        }

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            fillComboes();
            VRM1_STATE = VRM2_STATE = BRG1_STATE = BRG2_STATE = false;
        }

        // UI Events
        private void fillComboes()
        {
            ranges.ToList().ForEach(x => { cmbRangeScale.Items.Add(x); });
            rings.ToList().ForEach(x => { cmbRingScale.Items.Add(x); });
            cmbRangeScale.SelectedIndex = 4;
            cmbRingScale.SelectedIndex = 3;

            cmbDisplayMode.Items.Add("COURSE UP");
            cmbDisplayMode.Items.Add("NORTH UP");
            cmbDisplayMode.SelectedIndex = 0;

        }

        private void btnHamburger_Click(object sender, RoutedEventArgs e)
        {
            splitMainMenu.IsPaneOpen = !splitMainMenu.IsPaneOpen;
        }

        private void btnFullScreen_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(FullScreenPage));
        }

        private void btnSetup_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(SetupPage));
        }

        private void cmbRangeScale_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (cmbRangeScale.SelectedIndex < 0)
                return;
            var i = Convert.ToSingle(cmbRangeScale.SelectedItem);
            SelectedRange = i;

            switch ((int)SelectedRange)
            {
                case 0:
                case 1:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 0;
                    break;
                case 3:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 1;
                    break;
                case 6:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 3;
                    break;
                case 8:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 2;
                    break;
                case 12:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 3;
                    break;
                case 24:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 3;
                    break;
                case 48:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 4;
                    break;
                case 64:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 4;
                    break;
                case 96:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 4;
                    break;
                default:
                    cmbRingScale.SelectedIndex = -1;
                    cmbRingScale.SelectedIndex = 0;
                    break;
            }
        }

        private void cmbRingScale_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (cmbRingScale.SelectedIndex < 0)
                return;
            var i = Convert.ToSingle(cmbRingScale.SelectedItem);
            if (i == 0) { SelectedRing = 1; } else { SelectedRing = i; }
            RingInterval = SelectedRange / SelectedRing;
            txtRingInterval.Text = "INT: " + RingInterval + " nm.";
        }

        private void cmbDisplayMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (cmbDisplayMode.SelectedIndex > 0)
                RadarDisplay = DisplayMode.NORTH_UP;
            else
                RadarDisplay = DisplayMode.COURSE_UP;
        }

        private void btnAboutPage_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(AboutPage));
        }

        private void chkRings_Checked(object sender, RoutedEventArgs e)
        {
            chkRingsValue = true;   
        }

        private void chkRings_Unchecked(object sender, RoutedEventArgs e)
        {
            chkRingsValue = false;
        }

        private void chkHeadLine_Checked(object sender, RoutedEventArgs e)
        {
            chkHeadLineValue = true;
        }

        private void chkHeadLine_Unchecked(object sender, RoutedEventArgs e)
        {
            chkHeadLineValue = false;
        }

        private void slideVRM1_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            VRM1 = (float)e.NewValue; txtVRM1.Text = (SelectedRange * VRM1).ToString("N2") + " nm";
        }

        private void slideVRM2_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            VRM2 = (float)e.NewValue; txtVRM2.Text = (SelectedRange * VRM2).ToString("N2") + " nm";
        }

        private void tbtnVRM2_Click(object sender, RoutedEventArgs e)
        {
            VRM2_STATE = (bool)((ToggleButton)sender).IsChecked;
        }
        
        private void tbtnBRG1_Click(object sender, RoutedEventArgs e)
        {
            BRG1_STATE = (bool)((ToggleButton)sender).IsChecked;
            BRG1 = (int)slideBRG1.Value;
            CalcBRG1HK(BRG1);
        }

        private void tbtnBRG2_Click(object sender, RoutedEventArgs e)
        {
            BRG2_STATE = (bool)((ToggleButton)sender).IsChecked;
            BRG2 = (int)slideBRG2.Value;
            CalcBRG2HK(BRG2);
        }

        private void slideBRG1_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            BRG1 = (int)e.NewValue;
            CalcBRG1HK((float)e.NewValue);
        }

        private void slideBRG2_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            BRG2 = (int)e.NewValue;
            CalcBRG2HK((float)e.NewValue);
        }

        private void tbtnVRM1_Click(object sender, RoutedEventArgs e)
        {
            VRM1_STATE = (bool)((ToggleButton)sender).IsChecked;
        }
        
        private void Page_Unloaded(object sender, RoutedEventArgs e)
        {   // Dispose in Proper
            canViewPort.RemoveFromVisualTree();
            canViewPort = null;
        }

        // Canvas Draw Loop
        private void canViewPort_Draw(Microsoft.Graphics.Canvas.UI.Xaml.ICanvasAnimatedControl sender, Microsoft.Graphics.Canvas.UI.Xaml.CanvasAnimatedDrawEventArgs args)
        {
            ds = args.DrawingSession;
            if (sender != null)
            {
                if (canViewPort.Size.Width == null || canViewPort.Size.Width == null) //bugfix for stupid uwp unknown null-ref-exeption
                    return;

                w = (float)canViewPort.Size.Width;  // (float)((CanvasAnimatedControl)sender).Height;
                h = (float)canViewPort.Size.Height; // (float)((CanvasAnimatedControl)sender).Width; 
                origin = new Vector2(w / 2, h / 2);
            }

            if (h < w)
            { radius = (h - SCR_MARGIN) / 2; font_scale = h / w; }
            else
            { radius = (w - SCR_MARGIN) / 2; font_scale = w / h; }

            // DarkGray SCR_BACKGROUND
            ds.Clear(Color.FromArgb(255, 32, 32, 32));
            // Draw Skop BG
            ds.FillCircle(origin, (float)radius /* *1.25f  DEBUG PARAM */, Colors.DarkBlue);

            DrawEchoMask();
            DrawSkop(ds);
            DrawRings(ds);
            DrawVariableRangeMarkers();
            DrawBearingMarkers();
        }

        // Radar Drawings
        private void DrawEchoMask()
        {
            using (ds.CreateLayer(1f))
            {
                float i = 0;
                while (i < radius / 4)
                {
                    ds.DrawCircle(origin, (float)radius + i, Color.FromArgb(255, 32, 32, 32)); i += 0.1f;
                }
            }
        }

        private void DrawSkop(CanvasDrawingSession ds)
        {
            int c = 0;
            if (RadarDisplay == DisplayMode.NORTH_UP)
                c = (int)COURSE;

            //ds.FillCircle(origin, (float)radius, Colors.DarkBlue);
            ds.FillCircle(origin, 2.0f, SCOPE_PEN_COLOR); // Pivot point
            
            // Draw Head-Up Line
            if(chkHeadLineValue) 
            {
                Vector2 end_point = new Vector2(LineCoord(0, (float)radius, origin.X)[0], LineCoord(0, (float)radius, origin.Y)[1]);
                ds.DrawLine(origin, end_point, SCOPE_PEN_COLOR, 1.0f);
            }
            
            // Draw ruler lines
            var brush = new CanvasSolidColorBrush(ds.Device, SCOPE_PEN_COLOR);
            float r_start = (float)radius;
            float r_stop = r_start + 5;
            float rb_stop = r_start + 10;
            float rt_start = rb_stop + 12;

            for (int i = 0; i < 360; i++)
            {
                Vector2 start_point = new Vector2(LineCoord(i + c, r_start, origin.X)[0], LineCoord(i + c, r_start, origin.Y)[1]);
                Vector2 stop_point  = new Vector2(LineCoord(i + c, r_stop, origin.X)[0], LineCoord(i + c, r_stop, origin.Y)[1]);
                ds.DrawLine(start_point, stop_point, SCOPE_PEN_COLOR, 1.0f);
                // Draw thick lines
                if (i % 5 == 0)
                {
                    stop_point = new Vector2(LineCoord(i + c, r_stop + 2.5f, origin.X)[0], LineCoord(i + c, r_stop + 2.5f, origin.Y)[1]);
                    ds.DrawLine(start_point, stop_point, SCOPE_PEN_COLOR, 1.0f);
                }
                if (i%10==0)
                {
                    stop_point = new Vector2(LineCoord(i + c, rb_stop, origin.X)[0], LineCoord(i + c, rb_stop, origin.Y)[1]);
                    ds.DrawLine(start_point, stop_point, SCOPE_PEN_COLOR, 1.0f);

                    // Draw angle marks
                    string mark = i.ToString("000");
                    CanvasTextFormat ctf = new CanvasTextFormat();
                    ctf.FontSize = 12 * font_scale;
                    float font_wide = (ctf.FontSize * mark.Length);

                    Vector2 start_text = new Vector2(
                        LineCoord(i + c, rt_start , origin.X)[0] - (font_wide * .25f), 
                        LineCoord(i + c, rt_start , origin.Y - (ctf.FontSize * .75f ))[1]);

                    Rect rect = new Rect(start_text.X, start_text.Y, font_wide, ctf.FontSize);

                    if (i%90 == 0)
                        ds.DrawText(mark, rect, SCOPE_TEXT_HEADER_COLOR, ctf);
                    else
                        ds.DrawText(mark, rect, SCOPE_TEXT_COLOR, ctf);
                }
            }
        }

        private void DrawRings(CanvasDrawingSession ds)
        {
            if (chkRingsValue == false || (int)SelectedRing == 0)
                return;

            for (int i = 1; i < (int)SelectedRing; i++)
            {
                var segment = radius / SelectedRing;
                var s = (segment * i);
                ds.DrawCircle(origin.X, origin.Y, (float)s, SCOPE_PEN_COLOR);
            }
        }

        private void DrawVariableRangeMarkers()
        {
            if (VRM1_STATE)
            {
                var style = new CanvasStrokeStyle() { DashStyle = CanvasDashStyle.Dash };
                var s = VRM1 * radius;
                ds.DrawCircle(origin.X, origin.Y, (float)s, SCOPE_PEN_COLOR, 1.0f, style);
            }
            if (VRM2_STATE)
            {
                var style = new CanvasStrokeStyle() { DashStyle = CanvasDashStyle.Dot };
                var s = VRM2 * radius;
                ds.DrawCircle(origin.X, origin.Y, (float)s, SCOPE_PEN_COLOR, 1.0f, style);
            }
        }

        private void DrawBearingMarkers()
        {
            if (BRG1_STATE)
            {
                var style = new CanvasStrokeStyle() { DashStyle = CanvasDashStyle.Dash };

                Vector2 end_point = new Vector2(LineCoord(BRG1HK, (float)radius, origin.X)[0], LineCoord(BRG1HK, (float)radius, origin.Y)[1]);
                ds.DrawLine(origin, end_point, SCOPE_PEN_COLOR, 1.0f, style);
            }

            if (BRG2_STATE)
            {
                var style = new CanvasStrokeStyle() { DashStyle = CanvasDashStyle.Dash };

                Vector2 end_point = new Vector2(LineCoord(BRG2HK, (float)radius, origin.X)[0], LineCoord(BRG2HK, (float)radius, origin.Y)[1]);
                ds.DrawLine(origin, end_point, SCOPE_PEN_COLOR, 1.0f, style);
            }
        }

    }

    public enum DisplayMode { COURSE_UP, NORTH_UP }
}
