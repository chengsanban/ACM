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

	// Create objects.
	res |= D3DXCreateTeapot(pDirect3DDevice9, &Objects[0], 0);
	res |= D3DXCreateSphere(pDirect3DDevice9, 1.0f, 20, 20, &Objects[1], 0);
	res |= D3DXCreateTorus(pDirect3DDevice9, 0.5f, 1.0f, 20, 20, &Objects[2], 0);
	res |= D3DXCreateCylinder(pDirect3DDevice9, 0.5f, 0.5f, 2.0f, 20, 20, &Objects[3], 0);

	// Build world matrices - position the objects in world space.
	D3DXMatrixTranslation(&Worlds[0], 0.0f, 2.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[1], 0.0f, -2.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[2], -2.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[3], 2.0f, 0.0f, 0.0f);

	// Setup the object's materials.
	Mtrls[0] = RED_MTRL;
	Mtrls[1] = BLUE_MTRL;
	Mtrls[2] = GREEN_MTRL;
	Mtrls[3] = YELLOW_MTRL;

#if DIRECTION_LIGHT
	// Setup a directional light.
	D3DXVECTOR3 dir(1.0f, -0.0f, 0.25f);
	D3DXCOLOR   c = WHITE;
	Light = InitDirectionalLight(&dir, &c);
#elif POINT_LIGHT
	// Setup a point light.  Note that the point light
	// is positioned at the origin.
	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
	D3DXCOLOR   c = WHITE;
	Light = InitPointLight(&pos, &c);
#elif SPOT_LIGHT
	// Setup a spot light
	D3DXVECTOR3 pos(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 dir(0.0f, 0.0f, 1.0f);
	D3DXCOLOR   c = WHITE;
	 Light = InitSpotLight(&pos, &dir, &c);

	D3DXMATRIX Rx;
	D3DXMatrixRotationX(&Rx, D3DX_PI * 0.5f);
	Worlds[3] = Rx * Worlds[3];

	for (int i = 0; i < 4; i++)
		Mtrls[i].Power = 20.0f;

	//
	// Position and aim the camera.
	//
	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	pDirect3DDevice9->SetTransform(D3DTS_VIEW, &V);
#endif
	// Set and Enable the light.
	res |= pDirect3DDevice9->SetLight(0, &Light);
	res |= pDirect3DDevice9->LightEnable(0, true);

	// Set lighting related render states.
	res |= pDirect3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	res |= pDirect3DDevice9->SetRenderState(D3DRS_SPECULARENABLE, false);


	// Set the projection matrix.
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

HRESULT Present()
{
	HRESULT res = S_OK;
	if (pDirect3DDevice9)
	{

#if SPOT_LIGHT
		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			Light.Direction.x -= 5.0f * 0.01;

		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			Light.Direction.x += 5.0f * 0.01;

		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			Light.Direction.y += 5.0f * 0.01;

		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			Light.Direction.y -= 5.0f * 0.01;

		// update the light 
		pDirect3DDevice9->SetLight(0, &Light);
		pDirect3DDevice9->LightEnable(0, true);
#else
		// Update the scene: update camera position.
		static float angle = (3.0f * D3DX_PI) / 2.0f;
		static float height = 5.0f;

		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
			angle -= 0.5f * 1;

		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			angle += 0.5f * 1;

		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			height += 5.0f * 1;

		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			height -= 5.0f * 1;

		D3DXVECTOR3 position(cosf(angle) * 7.0f, height, sinf(angle) * 7.0f);
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);

		pDirect3DDevice9->SetTransform(D3DTS_VIEW, &V);
#endif
		// Draw the scene:
		res |= pDirect3DDevice9->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		res |= pDirect3DDevice9->BeginScene();

		for (int i = 0; i < 4; i++)
		{
			// set material and world matrix for ith object, then render
			// the ith object.
			res |= pDirect3DDevice9->SetMaterial(&Mtrls[i]);
			res |= pDirect3DDevice9->SetTransform(D3DTS_WORLD, &Worlds[i]);
			res |= Objects[i]->DrawSubset(0);
		}

		res |= pDirect3DDevice9->EndScene();
		res |= pDirect3DDevice9->Present(0, 0, 0, 0);
	}
	return res;
}

void CleanUp()
{
	SAFE_RELEASE(pDirect3D9);
	SAFE_RELEASE(pDirect3DDevice9);
	for (int i = 0; i < 4; i++)
		SAFE_RELEASE(Objects[i]);
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