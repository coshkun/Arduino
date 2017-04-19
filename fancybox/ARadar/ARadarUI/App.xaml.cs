using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
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

namespace ARadarUI
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    sealed partial class App : Application
    {
        public ApplicationDataContainer LocalSettings = ApplicationData.Current.LocalSettings;
        public StorageFolder LocalFolder = ApplicationData.Current.LocalFolder;
        private ApplicationDataCompositeValue _ARadarCurrentConfig, _ARadarDefaultConfig;
        //Props
        public ApplicationDataCompositeValue ARadarCurrentConfig {
            get { return (ApplicationDataCompositeValue)LocalSettings.Values["defaultSettings"]; } set { } }
        public ApplicationDataCompositeValue ARadarDefaultConfig {
            get { return (ApplicationDataCompositeValue)LocalSettings.Values["currentSettings"]; } set { } }

        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            this.InitializeComponent();
            this.Suspending += OnSuspending;
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="e">Details about the launch request and process.</param>
        protected override void OnLaunched(LaunchActivatedEventArgs e)
        {
#if DEBUG
            if (System.Diagnostics.Debugger.IsAttached)
            {
                this.DebugSettings.EnableFrameRateCounter = false;
            }
#endif
            GetARadarSettings();

            Frame rootFrame = Window.Current.Content as Frame;

            // Do not repeat app initialization when the Window already has content,
            // just ensure that the window is active
            if (rootFrame == null)
            {
                // Create a Frame to act as the navigation context and navigate to the first page
                rootFrame = new Frame();

                rootFrame.NavigationFailed += OnNavigationFailed;

                if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
                {
                    //TODO: Load state from previously suspended application
                }

                // Place the frame in the current Window
                Window.Current.Content = rootFrame;
            }

            if (e.PrelaunchActivated == false)
            {
                if (rootFrame.Content == null)
                {
                    // When the navigation stack isn't restored navigate to the first page,
                    // configuring the new page by passing required information as a navigation
                    // parameter
                    rootFrame.Navigate(typeof(MainPage), e.Arguments);
                }
                // Ensure the current window is active
                Window.Current.Activate();
            }
        }

        private void GetARadarSettings()
        {
            // Debug only (ne yaptınızı bilmiyorsanız dokunmayın)
            //LocalSettings.Values.Remove("defaultSettings");
            //LocalSettings.Values.Remove("currentSettings");

            // Read data from a composite setting
            var defaults = (ApplicationDataCompositeValue)LocalSettings.Values["defaultSettings"];
            var current = (ApplicationDataCompositeValue)LocalSettings.Values["currentSettings"];
            
            if (current == null)
            {
                if (defaults == null)
                {
                    // No data, lets create the defaults here.
                    _ARadarDefaultConfig = new ApplicationDataCompositeValue();
                    _ARadarDefaultConfig["ui_dark_theme"] = (bool)false;
                    _ARadarDefaultConfig["device_port_number"] = (int)4;
                    _ARadarDefaultConfig["device_port_speed"] = (int)57600;
                    _ARadarDefaultConfig["device_buffer_file_logging"] = (bool)false;
                    _ARadarDefaultConfig["device_utc_time"] = (string)DateTime.Now.ToBinary().ToString();
                    

                    // Save Settings
                    LocalSettings.Values.Add("defaultSettings", _ARadarDefaultConfig);

                    _ARadarCurrentConfig = new ApplicationDataCompositeValue();
                    _ARadarDefaultConfig.Select( x=> new { x.Key , x.Value } )
                        .ToList().ForEach(i => { _ARadarCurrentConfig.Add(i.Key, i.Value); });

                    LocalSettings.Values.Add("currentSettings", _ARadarCurrentConfig);
                }
                else
                {
                    // there is defaut settings from previous but no curent
                    // recover sys defaults
                    _ARadarDefaultConfig = defaults;
                    // duplicate to current
                    _ARadarCurrentConfig = new ApplicationDataCompositeValue();
                    _ARadarDefaultConfig.Select(x => new { x.Key, x.Value })
                        .ToList().ForEach(i => { _ARadarCurrentConfig.Add(i.Key, i.Value); });

                    LocalSettings.Values.Add("currentSettings", _ARadarCurrentConfig);
                } 
            }
            else
            {
                // there is current settings from previous, read from system
                _ARadarCurrentConfig = current;
            }

            // Publish to App
            ARadarCurrentConfig = _ARadarCurrentConfig;
            ARadarDefaultConfig = _ARadarDefaultConfig;
        }

        /// <summary>
        /// Invoked when Navigation to a certain page fails
        /// </summary>
        /// <param name="sender">The Frame which failed navigation</param>
        /// <param name="e">Details about the navigation failure</param>
        void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }

        /// <summary>
        /// Invoked when application execution is being suspended.  Application state is saved
        /// without knowing whether the application will be terminated or resumed with the contents
        /// of memory still intact.
        /// </summary>
        /// <param name="sender">The source of the suspend request.</param>
        /// <param name="e">Details about the suspend request.</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            //TODO: Save application state and stop any background activity
            deferral.Complete();
        }
    }
}
