package com.example.ess // Declares package name for the class

import android.content.Context // Imports Context class from Android framework
import android.graphics.Canvas // Imports Canvas class for drawing
import android.graphics.Color // Imports Color class for setting colors
import android.graphics.Paint // Imports Paint class for drawing styles
import android.util.AttributeSet // Imports AttributeSet class for view attributes
import android.view.SurfaceHolder // Imports SurfaceHolder class for managing the surface
import android.view.SurfaceView // Imports SurfaceView class for drawing surfaces

class VulkanView @JvmOverloads constructor( // Declares a class named VulkanView
    context: Context, // Context parameter for the constructor
    attrs: AttributeSet? = null // AttributeSet parameter for the constructor
) : SurfaceView(context, attrs), SurfaceHolder.Callback { // Extends SurfaceView class and implements SurfaceHolder.Callback interface
    private val paint: Paint = Paint() // Initializes a Paint object for drawing

    init { // Initialization block
        holder.addCallback(this) // Adds a callback to SurfaceHolder
        paint.color = Color.BLUE // Sets paint color to blue
    }

    override fun surfaceCreated(holder: SurfaceHolder) { // Overrides the method called when the surface is created
        val canvas = holder.lockCanvas() // Locks the canvas for drawing
        drawAxis(canvas) // Draws X and Y axes on the canvas
        drawDDALine(canvas, -18, 24, 30, -12) // Draws a line using DDA Algorithm
        holder.unlockCanvasAndPost(canvas) // Unlocks the canvas and posts the changes
    }

    private fun drawAxis(canvas: Canvas) { // Method to draw X and Y axes
        // Draw X axis
        canvas.drawLine(0f, height / 2.toFloat(), width.toFloat(), height / 2.toFloat(), paint) // Draws X axis line
        // Draw Y axis
        canvas.drawLine(width / 2.toFloat(), 0f, width / 2.toFloat(), height.toFloat(), paint) // Draws Y axis line
        // Label axes
        paint.textSize = 30f // Sets text size for labels
        paint.color = Color.RED // Sets text color to red
        canvas.drawText("X", width - 20.toFloat(), height / 2 - 10.toFloat(), paint) // Draws label for X axis
        canvas.drawText("Y", width / 2 + 10.toFloat(), 30.toFloat(), paint) // Draws label for Y axis
    }

    private fun drawDDALine(canvas: Canvas, x1: Int, y1: Int, x2: Int, y2: Int) { // Method to draw line using DDA Algorithm
        var x = x1.toFloat() // Converts x1 to float
        var y = y1.toFloat() // Converts y1 to float
        val dx = x2 - x1 // Calculates change in x
        val dy = y2 - y1 // Calculates change in y
        val steps = Math.max(Math.abs(dx), Math.abs(dy)) // Calculates the number of steps
        val xIncrement = dx.toFloat() / steps // Calculates the increment for x
        val yIncrement = dy.toFloat() / steps // Calculates the increment for y

        for (i in 0..steps) { // Iterates over each step
            canvas.drawPoint(x + width / 2.toFloat(), height / 2.toFloat() - y, paint) // Draws a point on the canvas
            x += xIncrement // Updates x for the next step
            y += yIncrement // Updates y for the next step
        }
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) { // Overrides the method called when the surface is changed
        // No implementation needed
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) { // Overrides the method called when the surface is destroyed
        // No implementation needed
    }
}
