using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using ARadarUI;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace ARadarUI.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class SetupPage : Page
    {
        ApplicationDataCompositeValue varsayilan_ayarlar, aktif_ayarlar;
        int[] speads = { 2400, 4800, 9600, 38400, 57600, 115200, 172800 };

        public SetupPage()
        {
            this.InitializeComponent();
            varsayilan_ayarlar = (ApplicationDataCompositeValue)ApplicationData.Current.LocalSettings.Values["defaultSettings"];
            aktif_ayarlar = (ApplicationDataCompositeValue)ApplicationData.Current.LocalSettings.Values["currentSettings"]; // App.ARadarCurrentConfig;
        }

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            for (int i = 1; i <= 15; i++)
                cmbPortNo.Items.Add(i);
            foreach (int i in speads)
                cmbPortSpeed.Items.Add(i);

            ResetToCurrentSetings();
        }

        // UI Events
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

        private void btnAboutPage_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(AboutPage));
        }

        private void btnHome_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }

        private void btnSettingsBack_Click(object sender, RoutedEventArgs e)
        {
            Frame.GoBack();
        }

        private void btnSettingsContent_Click(object sender, RoutedEventArgs e)
        {
            flipView.SelectedIndex = 0;
        }

        private void btnSettingsLicence_Click(object sender, RoutedEventArgs e)
        {
            flipView.SelectedIndex = 1;
        }

        private void btnResetSettings_Click(object sender, RoutedEventArgs e)
        {
            ResetDefaultSettings();
        }

        private void btnDiscardSettings_Click(object sender, RoutedEventArgs e)
        {
            ResetToCurrentSetings();
        }

        private void btnSaveSettings_Click(object sender, RoutedEventArgs e)
        {
            SaveCurrentSettings();
        }

        private void toggleTheme_Toggled(object sender, RoutedEventArgs e)
        {

        }

        // Functions
        private void ResetDefaultSettings()
        {
            toggleTheme.IsOn = (bool)varsayilan_ayarlar["ui_dark_theme"];
            chkLogBuffer.IsChecked = (bool)varsayilan_ayarlar["device_buffer_file_logging"];
            cmbPortNo.SelectedItem = (int)varsayilan_ayarlar["device_port_number"];
            cmbPortSpeed.SelectedItem  = (int)varsayilan_ayarlar["device_port_speed"];
            var str = Convert.ToInt64( (string)varsayilan_ayarlar["device_utc_time"] );
            DateTime vars_d = DateTime.FromBinary(str);
            dtpDatePicker.Date = new DateTimeOffset(vars_d);
            dtpTimePicker.Time = new TimeSpan(vars_d.Ticks);
            txtSeconds.Text = vars_d.Second.ToString();
            txtMiliSeconds.Text = vars_d.Millisecond.ToString();
        }

        private void ResetToCurrentSetings()
        {
            toggleTheme.IsOn = (bool)aktif_ayarlar["ui_dark_theme"];
            chkLogBuffer.IsChecked = (bool)aktif_ayarlar["device_buffer_file_logging"];
            cmbPortNo.SelectedItem = (int)aktif_ayarlar["device_port_number"];
            cmbPortSpeed.SelectedItem = (int)aktif_ayarlar["device_port_speed"];
            var str = Convert.ToInt64((string)aktif_ayarlar["device_utc_time"]);
            DateTime vars_d = DateTime.FromBinary(str);
            dtpDatePicker.Date = new DateTimeOffset(vars_d);
            dtpTimePicker.Time = new TimeSpan(vars_d.Ticks);
            txtSeconds.Text = vars_d.Second.ToString();
            txtMiliSeconds.Text = vars_d.Millisecond.ToString();
        }

        private void SaveCurrentSettings()
        {
            ApplicationDataCompositeValue adcv = new ApplicationDataCompositeValue();
            adcv["ui_dark_theme"] = (bool)toggleTheme.IsOn;
            adcv["device_buffer_file_logging"] = (bool)chkLogBuffer.IsChecked;
            adcv["device_port_number"] = (int)cmbPortNo.SelectedItem;
            adcv["device_port_speed"] = (int)cmbPortSpeed.SelectedItem;


            DateTime dt = new DateTime( dtpDatePicker.Date.Year,
                                        dtpDatePicker.Date.Month,
                                        dtpDatePicker.Date.Day,
                                        dtpTimePicker.Time.Hours,
                                        dtpTimePicker.Time.Minutes,
                                        Convert.ToInt32(txtSeconds.Text.Trim()),
                                        Convert.ToInt32(txtMiliSeconds.Text.Trim())
                                        );
            adcv["device_utc_time"] = (string)dt.ToBinary().ToString();


            ApplicationData.Current.LocalSettings.Values.Remove("currentSettings");
            ApplicationData.Current.LocalSettings.Values.Add("currentSettings", adcv);
            //Save it all
            //adcv.Select(x => new { x.Key, x.Value })
            //            .ToList().ForEach(i => { aktif_ayarlar.Add(i.Key, i.Value); });
            

        }
    }
}
