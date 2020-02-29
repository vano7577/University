#include "stdafx.h"
#include "editor.h"
#include "shape_editor.h"

static ShapeEditor *pse = NULL;

ShapeObjectsEditor::~ShapeObjectsEditor()
{
	free(pse);
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd)
{
	if (pse) pse->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd)
{
	if (pse) pse->OnLBup(hWnd);
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
	if (pse) pse->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnPaint(HWND hWnd)
{
	if (pse) pse->OnPaint(hWnd);
}

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	if (pse) pse->OnInitMenuPopup(hWnd, wParam);
}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd)
{
	if (pse) free(pse);
	pse = new PointEditor();

}

void ShapeObjectsEditor::StartLineEditor(HWND hWnd)
{
	if (pse) free(pse);
	pse = new LineEditor();

}

void ShapeObjectsEditor::StartRectEditor(HWND hWnd)
{
	if (pse) free(pse);
	pse = new RectEditor();
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd)
{
	if (pse) free(pse);
	pse = new EllipseEditor();
}