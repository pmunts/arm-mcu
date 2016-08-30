using Android.App;
using Android.Content.PM;
using Android.Text;
using Android.Views;
using Android.Views.InputMethods;
using Android.Widget;
using Android.OS;

using System;
using System.Net.Sockets;
using System.Threading;

namespace thermometer
{
    [Activity(Label = "@string/app_label", MainLauncher = true, Icon = "@drawable/icon", ScreenOrientation = ScreenOrientation.Portrait)]
    public class MainActivity : Activity
    {
        private EditText servername;
        private Button connectbutton;
        private TextView outputbox;
        private TextView tempdisplay;
        private InputMethodManager inputmanager;
        private volatile bool connected_flag = false;
        private volatile bool disconnect_flag = false;

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);

            // Get handles to UI widgets

            servername = FindViewById<EditText>(Resource.Id.servername);
            connectbutton = FindViewById<Button>(Resource.Id.connectbutton);
            outputbox = FindViewById<TextView>(Resource.Id.outputbox);
            tempdisplay = FindViewById<TextView>(Resource.Id.tempdisplay);

            // Connect event handlers

            servername.Click += servername_click;
            servername.KeyPress += servername_keypress;
            connectbutton.Click += connectbutton_click;

            // Get input manager, so we can dismiss the on screen keyboard at will

            inputmanager = (InputMethodManager)GetSystemService(InputMethodService);
        }

        // User clicked in the servername field

        private void servername_click(object sender, EventArgs e)
        {
            servername.SetCursorVisible(true);
        }

        // User typed in the servername field

        private void servername_keypress(object sender, View.KeyEventArgs e)
        {
            // Check for ENTER key

            if (e.Event.Action == KeyEventActions.Down && e.KeyCode == Keycode.Enter)
            {
                if (servername.Text.Length > 0)
                {
                    ConnectToServer();
                }

                // Consume the keypress

                e.Handled = true;
            }
            else
            {
                outputbox.Text = "";
                e.Handled = false;
            }
        }

        // User pressed the CONNECT/DISCONNECT button

        private void connectbutton_click(object sender, EventArgs e)
        {
            if (connectbutton.Text == GetString(Resource.String.button_connect))
            {
                if (servername.Text.Length > 0)
                {
                    ConnectToServer();
                }
            }

            if (connectbutton.Text == GetString(Resource.String.button_disconnect))
            {
                DisconnectFromServer();
            }
        }

        private void ConnectToServer()
        {
            // Turn off the cursor

            servername.SetCursorVisible(false);

            // Dismiss the on screen keyboard

            inputmanager.HideSoftInputFromWindow(servername.WindowToken, 0);

            // Lock the servername field and the connect button while the background thread is running

            servername.Enabled = false;
            connectbutton.Enabled = false;

            // Spawn a background worker thread

            ThreadPool.QueueUserWorkItem(o => BackgroundThread());
        }

        private void DisconnectFromServer()
        {
            if (connected_flag)
            {
                disconnect_flag = true;
            }
        }

        private void BackgroundThread()
        {
            try
            {
                // Open connection to the server

                RunOnUiThread(delegate { outputbox.Text = GetString(Resource.String.status_connecting) + " " + servername.Text + "..."; });

                TcpClient client = new TcpClient(servername.Text, 23);
                NetworkStream stream = client.GetStream();

                RunOnUiThread(delegate { outputbox.Text = ""; });

                connected_flag = true;

                // Change CONNECT button to DISCONNECT button

                RunOnUiThread(delegate { connectbutton.Text = GetString(Resource.String.button_disconnect); });
                RunOnUiThread(delegate { connectbutton.Enabled = true; });

                // Handle messages from the microcontroller

                while (!disconnect_flag)
                {
                    byte[] buffer = new byte[1024];
                    int len = stream.Read(buffer, 0, buffer.Length);

                    if (len > 0)
                    {
                        string s = System.Text.Encoding.UTF8.GetString(buffer, 0, len);

                        if (String.Equals("Temperature is ", s.Substring(0, 15)))
                        {
                            string T = s.Substring(15).Trim();
                            RunOnUiThread(delegate { tempdisplay.Text = T + " °C"; });
                        }
                        else
                        {
                            RunOnUiThread(delegate { tempdisplay.Text = "Error!"; });
                        }
                    }
                }

                // Tear down the connection
        
                stream.Close();
                client.Close();
            }
            catch (Exception ex)
            {
                // Display error message

                RunOnUiThread(delegate { outputbox.Text = ex.Message; });
            }
            finally
            {
                // Restore disconnected state

                connected_flag = false;
                disconnect_flag = false;

                RunOnUiThread(delegate { servername.Text = "";});
                RunOnUiThread(delegate { servername.Enabled = true; });
                RunOnUiThread(delegate { connectbutton.Text = GetString(Resource.String.button_connect); });
                RunOnUiThread(delegate { connectbutton.Enabled = true; });
                RunOnUiThread(delegate { tempdisplay.Text = ""; });
            }
        }
    }
}