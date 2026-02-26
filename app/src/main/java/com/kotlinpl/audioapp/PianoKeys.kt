package com.kotlinpl.audioapp

import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.BoxWithConstraints
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.offset
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.input.pointer.PointerEventType
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

@Composable
fun PianoKeys(modifier: Modifier = Modifier) {
    val whiteNotes = listOf(
        R.string.note_c,
        R.string.note_d,
        R.string.note_e,
        R.string.note_f,
        R.string.note_g,
        R.string.note_a,
        R.string.note_b
    )

    BoxWithConstraints(
        modifier = modifier
            .fillMaxWidth()
            .height(240.dp)
            .background(Color.White)
            .border(1.dp, Color.Black)
    ) {
        val scope = this
        val whiteKeyWidth = scope.maxWidth / 7
        val blackKeyWidth = whiteKeyWidth * 0.6f
        val blackKeyHeight = scope.maxHeight * 0.65f

        Row(modifier = Modifier.fillMaxSize()) {
            whiteNotes.forEach { noteRes ->
                WhiteKey(
                    note = stringResource(noteRes),
                    modifier = Modifier
                        .weight(1f)
                        .fillMaxHeight(),
                    onNoteTap = {},
                    onNoteRelease = {}
                )
            }
        }

        val blackKeyOffsets = listOf(
            1 to (R.string.note_c_sharp to R.string.note_d_flat),
            2 to (R.string.note_d_sharp to R.string.note_e_flat),
            4 to (R.string.note_f_sharp to R.string.note_g_flat),
            5 to (R.string.note_g_sharp to R.string.note_a_flat),
            6 to (R.string.note_a_sharp to R.string.note_b_flat)
        )

        blackKeyOffsets.forEach { (index, notes) ->
            BlackKey(
                sharpNote = stringResource(notes.first),
                flatNote = stringResource(notes.second),
                modifier = Modifier
                    .offset(x = whiteKeyWidth * index - blackKeyWidth / 2)
                    .size(blackKeyWidth, blackKeyHeight)
            )
        }
    }
}

@Composable
private fun WhiteKey(
    note: String,
    onNoteTap: () -> Unit,
    onNoteRelease: () -> Unit,
    modifier: Modifier = Modifier
) {
    var pointerEventType: PointerEventType? by remember { mutableStateOf(null) }


    Box(
        modifier = modifier
            .border(0.5.dp, Color.Black)
            .padding(bottom = 16.dp)
            .pointerInput(pointerEventType) {
                awaitPointerEventScope {
                    while (true) {
                        val event = awaitPointerEvent()
                    }
                }
            },
        contentAlignment = Alignment.BottomCenter
    ) {
        Text(
            text = note,
            fontSize = 24.sp,
            fontWeight = FontWeight.Medium,
            color = Color.Black
        )
    }
}

@Composable
private fun BlackKey(sharpNote: String, flatNote: String, modifier: Modifier = Modifier) {
    Box(
        modifier = modifier
            .background(Color.Black)
            .padding(bottom = 12.dp),
        contentAlignment = Alignment.BottomCenter
    ) {
        Column(horizontalAlignment = Alignment.CenterHorizontally) {
            Text(
                text = sharpNote,
                fontSize = 18.sp,
                fontWeight = FontWeight.Medium,
                color = Color.White
            )
            Spacer(modifier = Modifier.height(4.dp))
            Text(
                text = flatNote,
                fontSize = 18.sp,
                fontWeight = FontWeight.Medium,
                color = Color.White
            )
        }
    }
}

@Preview(showBackground = true)
@Composable
fun PianoKeysPreview() {
    MaterialTheme {
        Box(modifier = Modifier.padding(16.dp)) {
            PianoKeys()
        }
    }
}
