#include "D3d_Test_Project.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;

	//init d3d device
	if (FAILED(InitD3dDevice()))
		return FALSE;

	//set render status
	if (FAILED(Setup()))
		return FALSE;

	// Main msg loop
	while (msg.message != WM_QUIT)
	{
		//PeekMessage, not GetMessage
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(SLEEP_TIME);
			Present();
		}
	}
	CleanUp();
	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(NULL, IDI_ERROR);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(NULL, IDI_ERROR);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
 

   hInst = hInstance;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//d3d function

HRESULT InitD3dDevice()
{
	HRESULT res = S_OK;
	pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	pDirect3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	//check vertex processing style
	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//set d3d device param
	//D3DPRESENT_PARAMETERS Describes the presentation parameters.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; //32bit 24bit DepthStencil 8bit TemplateStencil
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	res = pDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &pDirect3DDevice9);
	
	return res;
}

HRESULT Setup()
{
	HRESULT res = S_OK;

	res |= SetupBaseScene();

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.25f, // 45 - degree
		(float)WIDTH / (float)HEIGHT,
		1.0f,
		1000.0f);
	res |= pDirect3DDevice9->SetTransform(D3DTS_PROJECTION, &proj);

	return res;
}

HRESULT SetupBaseScene()
{
	HRESULT res = S_OK;
		// they don't exist, create them
	res |= pDirect3DDevice9->CreateVertexBuffer(
			6 * sizeof(Vertex),
			0,
			FVF_VERTEX,
			D3DPOOL_MANAGED,
			&pfloorVertexBuffer,
			0);

	Vertex* v = 0;
	res |= pfloorVertexBuffer->Lock(0, 0, (void**)&v, 0);

	v[0] = Vertex(-20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[1] = Vertex(-20.0f, -2.5f, 20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[2] = Vertex(20.0f, -2.5f, 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	v[3] = Vertex(-20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[4] = Vertex(20.0f, -2.5f, 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	v[5] = Vertex(20.0f, -2.5f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	res |= pfloorVertexBuffer->Unlock();

	D3DXCreateCylinder(pDirect3DDevice9, 0.5f, 0.5f, 5.0f, 20, 20, &pPillarMesh, 0);

	D3DXCreateTextureFromFile(
		pDirect3DDevice9,
		L"desert.bmp",
		&pfloorTexture);

	return res;

}

HRESULT Present()
{
	HRESULT res = S_OK;
	if (pDirect3DDevice9)
	{
		// Update: Update the camera.

		if (::GetAsyncKeyState('W') & 0x8000f)
			TheCamera.walk(4.0f * scale);

		if (::GetAsyncKeyState('S') & 0x8000f)
			TheCamera.walk(-4.0f * scale);

		if (::GetAsyncKeyState('A') & 0x8000f)
			TheCamera.strafe(-4.0f * scale);

		if (::GetAsyncKeyState('D') & 0x8000f)
			TheCamera.strafe(4.0f * scale);

		if (::GetAsyncKeyState('R') & 0x8000f)
			TheCamera.fly(4.0f * scale);

		if (::GetAsyncKeyState('F') & 0x8000f)
			TheCamera.fly(-4.0f * scale);

		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			TheCamera.pitch(1.0f * scale);

		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			TheCamera.pitch(-1.0f * scale);

		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			TheCamera.yaw(-1.0f * scale);

		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			TheCamera.yaw(1.0f * scale);

		if (::GetAsyncKeyState('N') & 0x8000f)
			TheCamera.roll(1.0f * scale);

		if (::GetAsyncKeyState('M') & 0x8000f)
			TheCamera.roll(-1.0f * scale);

		// Update the view matrix representing the cameras 
		// new position/orientation.
		D3DXMATRIX V;
		TheCamera.getViewMatrix(&V);
		res |= pDirect3DDevice9->SetTransform(D3DTS_VIEW, &V);

		// Render
		res |= pDirect3DDevice9->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		res |= pDirect3DDevice9->BeginScene();

		res |= PresentBaseScene();

		res |= pDirect3DDevice9->EndScene();
		res |= pDirect3DDevice9->Present(0, 0, 0, 0);
	}
	return res;
}

HRESULT PresentBaseScene()
{
	HRESULT res = S_OK;

	res |= pDirect3DDevice9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	res |= pDirect3DDevice9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	res |= pDirect3DDevice9->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	D3DXVECTOR3 dir(0.707f, -0.707f, 0.707f);
	D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = InitDirectionalLight(&dir, &col);

	res |= pDirect3DDevice9->SetLight(0, &light);
	res |= pDirect3DDevice9->LightEnable(0, true);
	res |= pDirect3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	res |= pDirect3DDevice9->SetRenderState(D3DRS_SPECULARENABLE, true);

	// Render
	D3DXMATRIX T, R, P, S;

	D3DXMatrixScaling(&S, 1, 1, 1);

	// used to rotate cylinders to be parallel with world's y-axis
	D3DXMatrixRotationX(&R, -D3DX_PI * 0.5f);

	// draw floor
	D3DXMatrixIdentity(&T);
	T = T * S;
	res |= pDirect3DDevice9->SetTransform(D3DTS_WORLD, &T);
	res |= pDirect3DDevice9->SetMaterial(&WHITE_MTRL);
	res |= pDirect3DDevice9->SetTexture(0, pfloorTexture);
	res |= pDirect3DDevice9->SetStreamSource(0, pfloorVertexBuffer, 0, sizeof(Vertex));
	res |= pDirect3DDevice9->SetFVF(FVF_VERTEX);
	res |= pDirect3DDevice9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	// draw pillars
	res |= pDirect3DDevice9->SetMaterial(&BLUE_MTRL);
	res |= pDirect3DDevice9->SetTexture(0, 0);
	for (int i = 0; i < 5; i++)
	{
		D3DXMatrixTranslation(&T, -5.0f, 0.0f, -15.0f + (i * 7.5f));
		P = R * T * S;
		res |= pDirect3DDevice9->SetTransform(D3DTS_WORLD, &P);
		res |= pPillarMesh->DrawSubset(0);

		D3DXMatrixTranslation(&T, 5.0f, 0.0f, -15.0f + (i * 7.5f));
		P = R * T * S;
		res |= pDirect3DDevice9->SetTransform(D3DTS_WORLD, &P);
		res |= pPillarMesh->DrawSubset(0);
	}
	
	return res;
}

void CleanUp()
{
	SAFE_RELEASE(pDirect3D9);
	SAFE_RELEASE(pDirect3DDevice9);
}

void CleanUpBaseScene()
{
	SAFE_RELEASE(pfloorVertexBuffer);
	SAFE_RELEASE(pfloorTexture);
	SAFE_RELEASE(pPillarMesh);
}

D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = *color * 0.6f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_POINT;
	light.Ambient = *color * 0.6f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Position = *position;
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_SPOT;
	light.Ambient = *color * 0.0f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Position = *position;
	light.Direction = *direction;
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta = 0.4f;
	light.Phi = 0.9f;

	return light;
}

D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}

BoundingBox::BoundingBox()
{
	// infinite small 
	_min.x = I_INFINITY;
	_min.y = I_INFINITY;
	_min.z = I_INFINITY;

	_max.x = I_INFINITY;
	_max.y = I_INFINITY;
	_max.z = I_INFINITY;
}

bool BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if (p.x >= _min.x && p.y >= _min.y && p.z >= _min.z &&
		p.x <= _max.x && p.y <= _max.y && p.z <= _max.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

BoundingSphere::BoundingSphere()
{
	_radius = 0.0f;
}
