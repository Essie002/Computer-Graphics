package com.example.qd

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.util.AttributeSet
import android.view.SurfaceHolder
import android.view.SurfaceView

class VulkanView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null
) : SurfaceView(context, attrs), SurfaceHolder.Callback {

    // Paint object for drawing
    private val paint: Paint = Paint()

    init {
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        val canvas = holder.lockCanvas()
        drawAxis(canvas) // Draw X and Y axes
        drawBresenhamLine(canvas, 3, 4, 4, 8) // Draw line using Bresenham's Line Drawing Algorithm
        holder.unlockCanvasAndPost(canvas)
    }

    // Function to draw X and Y axes
    private fun drawAxis(canvas: Canvas) {
        paint.color = Color.BLACK // Set color to black for axes
        paint.strokeWidth = 2f // Set line width
        // Draw X axis
        canvas.drawLine(0f, height / 2.toFloat(), width.toFloat(), height / 2.toFloat(), paint)
        // Draw Y axis
        canvas.drawLine(width / 2.toFloat(), 0f, width / 2.toFloat(), height.toFloat(), paint)
        // Label axes
        paint.textSize = 30f
        canvas.drawText("X", width - 20.toFloat(), height / 2 - 10.toFloat(), paint)
        canvas.drawText("Y", width / 2 + 10.toFloat(), 30.toFloat(), paint)
    }

    // Function to draw a line using Bresenham's Line Drawing Algorithm
    private fun drawBresenhamLine(canvas: Canvas, x1: Int, y1: Int, x2: Int, y2: Int) {
        paint.color = Color.BLUE // Set color to blue for the line
        paint.strokeWidth = 5f // Set line width

        var x = x1
        var y = y1
        val dx = x2 - x1
        val dy = y2 - y1
        val dxAbs = Math.abs(dx)
        val dyAbs = Math.abs(dy)
        val sx = if (x1 < x2) 1 else -1
        val sy = if (y1 < y2) 1 else -1
        var err = dxAbs - dyAbs

        while (true) {
            canvas.drawPoint((x + width / 2).toFloat(), (height / 2 - y).toFloat(), paint) // Adjust for center of the canvas
            if (x == x2 && y == y2) break
            val err2 = 2 * err
            if (err2 > -dyAbs) {
                err -= dyAbs
                x += sx
            }
            if (err2 < dxAbs) {
                err += dxAbs
                y += sy
            }
        }
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {}

    override fun surfaceDestroyed(holder: SurfaceHolder) {}
}
