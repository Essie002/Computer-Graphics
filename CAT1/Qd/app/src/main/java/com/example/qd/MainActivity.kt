package com.example.qd // Package declaration

import android.content.Context // Importing required Android classes
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.util.AttributeSet
import android.view.SurfaceHolder
import android.view.SurfaceView

class CustomVulkanView @JvmOverloads constructor( // Class declaration for CustomVulkanView
    context: Context, // Constructor parameter: Context object
    attrs: AttributeSet? = null // Constructor parameter: AttributeSet object, with a default value of null
) : SurfaceView(context, attrs), SurfaceHolder.Callback { // Class inheritance and interface implementation

    // Paint object for drawing
    private val paint: Paint = Paint()

    init { // Initialization block
        holder.addCallback(this) // Attaching a SurfaceHolder.Callback to this CustomVulkanView
    }

    override fun surfaceCreated(holder: SurfaceHolder) { // Method called when the surface is created
        val canvas = holder.lockCanvas() // Locking the canvas to draw on it
        drawAxis(canvas) // Drawing X and Y axes
        drawBresenhamLine(canvas, 3, 4, 4, 8) // Drawing a line using Bresenham's Line Drawing Algorithm
        holder.unlockCanvasAndPost(canvas) // Unlocking the canvas and posting it to the surface
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

        while (true) { // Loop until the line is completely drawn
            // Drawing a point on the canvas (adjusting for the center of the canvas)
            canvas.drawPoint((x + width / 2).toFloat(), (height / 2 - y).toFloat(), paint)
            if (x == x2 && y == y2) break // Exit the loop when the line reaches the end point
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

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        // This method is called when the size or format of the surface changes.
        // It is typically used to adjust the rendering to match the new surface size.
        // However, in this implementation, it is not used, so the body of the method is left empty.
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        // This method is called when the surface associated with this SurfaceHolder is destroyed.
        // It is a good place to release resources associated with drawing, such as stopping animation or releasing bitmaps.
        // However, in this implementation, it is not used, so the body of the method is left empty.
    }
}
