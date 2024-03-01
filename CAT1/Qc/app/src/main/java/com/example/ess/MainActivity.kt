package com.example.ess // Package declaration

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
    private val paint: Paint = Paint() // Initializing a Paint object for drawing

    init { // Initialization block
        holder.addCallback(this) // Attaching a SurfaceHolder.Callback to this CustomVulkanView
        paint.color = Color.BLUE // Setting the paint color to blue
    }

    override fun surfaceCreated(holder: SurfaceHolder) { // Method called when the surface is created
        val canvas = holder.lockCanvas() // Locking the canvas to draw on it
        drawAxis(canvas) // Drawing X and Y axes
        drawDDALine(canvas, -18, 24, 30, -12) // Drawing a line using the DDA Algorithm
        holder.unlockCanvasAndPost(canvas) // Unlocking the canvas and posting it to the surface
    }

    private fun drawAxis(canvas: Canvas) { // Function to draw X and Y axes
        // Drawing X axis
        canvas.drawLine(0f, height / 2.toFloat(), width.toFloat(), height / 2.toFloat(), paint)
        // Drawing Y axis
        canvas.drawLine(width / 2.toFloat(), 0f, width / 2.toFloat(), height.toFloat(), paint)
        // Labeling axes
        paint.textSize = 30f
        paint.color = Color.RED
        canvas.drawText("X", width - 20.toFloat(), height / 2 - 10.toFloat(), paint)
        canvas.drawText("Y", width / 2 + 10.toFloat(), 30.toFloat(), paint)
    }

    private fun drawDDALine(canvas: Canvas, x1: Int, y1: Int, x2: Int, y2: Int) { // Function to draw a line using DDA algorithm
        var x = x1.toFloat()
        var y = y1.toFloat()
        val dx = x2 - x1
        val dy = y2 - y1
        val steps = Math.max(Math.abs(dx), Math.abs(dy))
        val xIncrement = dx.toFloat() / steps
        val yIncrement = dy.toFloat() / steps

        for (i in 0..steps) { // Iterating over the steps
            // Drawing a point on the canvas (adjusting for the center of the canvas)
            canvas.drawPoint(x + width / 2.toFloat(), height / 2.toFloat() - y, paint)
            x += xIncrement // Incrementing x
            y += yIncrement // Incrementing y
        }
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {} // Method called when the surface changes

    override fun surfaceDestroyed(holder: SurfaceHolder) {} // Method called when the surface is destroyed
}
