package com.kotlinpl.audioapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.kotlinpl.audio_management.AudioManagement
import com.kotlinpl.audioapp.ui.theme.AudioAppTheme

class MainActivity : ComponentActivity() {
    private val audioManagement = AudioManagement()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            AudioAppTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Row(
                        horizontalArrangement = Arrangement.Center,
                        modifier = Modifier.padding(innerPadding)
                    ) {
                        //
                        Button(
                            onClick = {
                                audioManagement.play()
                            }
                        ) { Text("Start Audio") }

                        Button(
                            onClick = {
                                audioManagement.stop()
                            }
                        ) { Text("Stop Audio") }
                    }
                }
            }
        }
    }

    override fun onStop() {
        super.onStop()

        audioManagement.stop()
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    AudioAppTheme {
        Greeting("Android")
    }
}