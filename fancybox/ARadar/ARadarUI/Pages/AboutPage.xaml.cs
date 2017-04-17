using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.ApplicationModel;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace ARadarUI
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class AboutPage : Page
    {
        public AboutPage()
        {
            this.InitializeComponent();
            txtAbout.Text = "ARadarUI " + GetAppVersion();
            txtDescription.Text = "Arduino Based Ulra-Sonic Radar User Interface.";
            string endDate = (DateTime.Now.Year > 2017) ? " - " + DateTime.Now.Year : "";
            txtCopyRight.Text = "@2017" + endDate +  " All Rights Reserved.";
            txtAbout.FontSize = 24.0f;
            txtCopyRight.FontSize = txtAbout.FontSize / 3;
            txtDescription.FontSize = txtAbout.FontSize / 2;

        }

        public static string GetAppVersion()
        {

            Package package = Package.Current;
            PackageId packageId = package.Id;
            PackageVersion version = packageId.Version;

            return string.Format("{0}.{1}.{2}.{3}", version.Major, version.Minor, version.Build, version.Revision);
        }

        // Nanigations
        private void btnAboutBack_Click(object sender, RoutedEventArgs e)
        {
            Frame.GoBack();
        }

        private void btnAboutContent_Click(object sender, RoutedEventArgs e)
        {
            flipView.SelectedIndex = 0;
        }

        private void btnAboutLicence_Click(object sender, RoutedEventArgs e)
        {
            flipView.SelectedIndex = 1;
        }
    }
}
