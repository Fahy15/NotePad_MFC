// NotePadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NotePad.h"
#include "NotePadDlg.h"
#include "About.h"
#include "resource.h"
#include "DataOperate.h"
#include "DataOperate.cpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef EQUAL
#define EQUAL 0x3d
#endif
enum operators { ADD = '+', SUBTRACT = '-', MULTIPLY = '*', DEVIDE = '/' };
/////////////////////////////////////////////////////////////////////////////
// CNotePadDlg dialog

CNotePadDlg::CNotePadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNotePadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNotePadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNotePadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotePadDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TEXT, editControl);
}

BEGIN_MESSAGE_MAP(CNotePadDlg, CDialog)
	//{{AFX_MSG_MAP(CNotePadDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_WM_CLOSE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_DATE, OnEditDate)
	ON_WM_SIZE()
	ON_WM_DROPFILES()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FORMAT_FONT, OnFormatFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotePadDlg message handlers

BOOL CNotePadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNotePadDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNotePadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//ʵ�ֹ��ڶԻ������ʾ
void CNotePadDlg::OnHelpAbout() 
{
	CAbout dlg;
	dlg.DoModal();
	
}

//����esc�˳�����
void CNotePadDlg::OnCancel() 
{
	//CDialog::OnCancel();
}

//����OnClose()ʵ��X���˳�����
void CNotePadDlg::OnClose() 
{
	OnFileExit();//������ò˵��µ��˳�����
	//EndDialog(IDCANCEL);
	//CDialog::OnClose();
}

//ʵ�ֲ˵���Ŀ�� ���ƵĹ���
void CNotePadDlg::OnEditCopy() 
{
	CEdit * pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
    pEdit->Copy();
}

//ʵ�ֲ˵���Ŀ�� ɾ���Ĺ���
void CNotePadDlg::OnEditClear() 
{
	CEdit * pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit->Clear();
}
//ʵ�ֲ˵���Ŀ�� �����Ĺ���
void CNotePadDlg::OnEditUndo() 
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit ->Undo();	
}

//ʵ�ֲ˵���Ŀ�� ���еĹ���
void CNotePadDlg::OnEditCut() 
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit ->Cut();
}
//ʵ�ֲ˵���Ŀ�� ȫѡ�Ĺ���
void CNotePadDlg::OnEditSelectAll() 
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit ->SetSel(0,-1);	
}
//ʵ�ֲ˵���Ŀ�� ճ���Ĺ���
void CNotePadDlg::OnEditPaste() 
{
	
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit ->Paste();	
}
//ʵ�ֲ˵���Ŀ�� ʱ��Ĺ���
void CNotePadDlg::OnEditDate() 
{
	CTime t = CTime::GetCurrentTime();

	CString str = t.Format("%Y��%m��%d�� %H:%M:%S");
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit ->ReplaceSel( str,TRUE);
}

//ʵ���ƶ����ڴ�С�Ĺ��ܣ��ǵ��޸Ĵ������Ե��е�ֵ
void CNotePadDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CWnd* pEdit = GetDlgItem(IDC_TEXT);
	if(pEdit)
		pEdit->MoveWindow(0,0,cx,cy);
	
}

//ʵ�ֲ˵����˳��Ĺ���
void CNotePadDlg::OnFileExit() 
{
	if(Prompt() == 0) //�������0������ѡ����ȡ������ô���رնԻ���
	{
		//�����κδ���
	}
	else//���������0 ��ô����ѡ���� ��  ֱ�ӹرնԻ���
	{
		EndDialog(IDCANCEL);	
	}
		
}

//ʵ����һ���ļ�����Ĺ���
void CNotePadDlg::OnDropFiles(HDROP hDropInfo) 
{	
	if(!Prompt())
		return;
	char szFile[MAX_PATH];
	UINT n = DragQueryFile(hDropInfo,0,szFile,sizeof(szFile));
	CString str = szFile ;
	n = str.ReverseFind('\\');
	if(n>0)
	{
		str = str.Mid(n+1);
		OpenFile(szFile,str);
	}

	CDialog::OnDropFiles(hDropInfo);
}

//ʵ�ֲ˵������½��Ĺ���
void CNotePadDlg::OnFileNew() 
{
	//�����ļ��ı�����������������½�һ���ļ���ʱ�򣬸ı���ԭ�����ڵ��ļ�
	//���==0������ȡ������ôֱ�ӷ��أ���ʾȡ���½�������
	//�����=0�� ��ô�Ϳ��ܱ��浱ǰ�ļ����߲����浱ǰ�ļ�
	if(Prompt() == 0)
		return;

	//Ȼ����������½��ļ�������
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit->SetWindowText("");
	m_szCurrentFile = "";
	SetTitle();

	
}

//ʵ�ֲ˵���Ŀ�´򿪵Ĺ���
void CNotePadDlg::OnFileOpen() 
{
	//������
	LPCTSTR szFilter = "�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||";
	//��һ���ļ�ѡ��Ի��� TRUE���� ���ļ�
	CFileDialog filedlg(TRUE,"txt","11",OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,
		szFilter);
	if(IDCANCEL== filedlg.DoModal())
		return;
	//���ļ�����ʾ��IDC_TEXT����
	OpenFile(filedlg.GetPathName(),filedlg.GetFileName());
}

//ʵ�ֲ˵���Ŀ�±���Ĺ���
void CNotePadDlg::OnFileSave() 
{
	//���Ҫ������ļ��ǵ�һ�α��棬��ô��ת���� ���Ϊ
	if(m_szCurrentFile.GetLength() == 0)
	{
		OnFileSaveAs();
		return;
	}
	
	CFile file;
	if(file.Open(m_szCurrentFile,CFile::modeWrite|CFile::modeCreate) == 0)
	{	
		OnFileSaveAs();
		return;
	
	}

	CString szText;
	GetDlgItemText(IDC_TEXT,szText);//�õ�Edit�ؼ����������
	file.Write(szText,szText.GetLength());//д��file����
	file.Close();//�رն���
		
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT) ;
	pEdit ->SetModify(FALSE);//FALSE��ʾ�ı�û�иı䣻����ֱ�ӱ��棬����˳���ʱ��Ҫ����ʾ�ı�

}

//ʵ�ֲ˵���Ŀ�����Ϊ�Ĺ���
void CNotePadDlg::OnFileSaveAs() 
{
	
	LPCTSTR szFilter = "�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||";
	//��ʼ���ļ��Ի��� FALSE�������ļ�
	CFileDialog filedlg(FALSE,"txt","11",OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST|
		OFN_FILEMUSTEXIST|OFN_CREATEPROMPT,szFilter);
	//���ļ��Ի���
	if(IDCANCEL == filedlg.DoModal())
		return;
	//�õ��ļ��Ի�����ѡ���ļ���·����
	CString szFile = filedlg.GetPathName();

	//����һ��CFile����
	CFile file;
	//���ļ�
	if( file.Open(szFile,CFile::modeWrite|CFile::modeCreate) == 0)
	{
		MessageBox(filedlg.GetFileName()+"�����ļ�ʱʧ��!", NULL,MB_ICONEXCLAMATION);
		return;
	}

	//��ǰ�ļ�Ϊ���ļ�����������
	m_szCurrentFile = szFile;

	CString strText;
	//�õ�IDC_TEXT�ؼ���������� 
	GetDlgItemText(IDC_TEXT,strText);
	//�ļ�д�룬��һ��������Ҫд������ݣ��ڶ�����д�����ݵĳ���
	file.Write(strText,strText.GetLength());

	/*
1:	Flush�ǽ�������������д���ļ�������ա���������4k�����ݣ���4k�ˣ�
	�ͻ��Զ�д���ļ��������Ļ�����Ҫflushһ�£������flush�Ļ����ļ�
	������п��ܻ���һЩ���� 
2:  Flush()��������ˢ�»��������������write������ɺ������Close()��
	�ǻ��������ǲ������ݾͶ�ʧ�ˣ���Ϊ����ʱ��д���ڴ�Ȼ���ڶ����ļ��ˡ�
	�����ڵ���Close()ǰ�ѻ�����������ǿ������������Ų��ᶪʧ���ݡ�
3:  flush()��������ǿ�ƽ�������������д����̣�ֻ��Ϊ��ȷ�����ݾ��챻д�룬������ʵ���С�����ݾ���flush(),��ôӲ��д��Ļ�е����ʱ������ԱȽϳ��ģ�
	���������flush(),�������ﵽһ�����������ͻ��Զ�д����̡�
	�ڹر��ļ���ʱ��Ҳ��ѻ����������ݣ�����У�ǿ��д�����
4:  ������Ƕ��߳�дͬһ���ļ������Բ���flush(),
	������ǰ�ǵ�close�Ϳ��ԣ���ȻҲ�������flushһ�Σ���close 
	*/
	file.Flush();//����Ľ��͸�����ˣ��ҿ�����������ˣ�������Ҳһ��

	file.Close();//�ر��ļ���ɾ������

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit ->SetModify(FALSE);
	SetTitle();
	
}

//ʵ�ֲ˵���Ŀ������ѡ��Ĺ���
void CNotePadDlg::OnFormatFont() 
{
	
	CFont* pFont = GetDlgItem(IDC_TEXT)->GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);//��õ�ǰCFont�����LOGFONT�ṹ��Ŀ���
	CFontDialog fd(&lf);//��������Ի��򣬳�ʼѡ������Ϊ��ǰCFont���������

	if(IDCANCEL == fd.DoModal())
		return;
	m_font.DeleteObject();//���m_font�Ѿ�������һ��������Դ�������ͷ���
	m_font.CreateFontIndirect(fd.m_cf.lpLogFont);//ʹ��ѡ�������LOGFONT�����µ����� 
//	m_font.CreateFontIndirect(&lf);
	GetDlgItem(IDC_TEXT)->SetFont(&m_font);//ѡ������
	
}

void CNotePadDlg::OpenFile(CString szFilePath, CString szFileName)
{

	CFile file;//����һ��CFile����

	//��һ���ļ�
	if(file.Open(szFilePath,CFile::modeRead) == 0)
	{
		MessageBox(szFileName+"���ļ�ʧ��!",NULL,MB_ICONEXCLAMATION);
		return;
	}
	/*
	int size = file.GetLength();//�õ��ļ��ĳ���
	char* pText = new char[size+1];//Ҫ�����ļ���������ָ��

	//��CFile����file������ļ������ݶ��뻺�塣
	int nRet = file.Read(pText,size);
	file.Close();//�رն���
	*/

	//�ڶ��ַ���
	CFileStatus fs;
	file.GetStatus(fs);
	char *pText = new char[fs.m_size+1];
	memset(pText,0,fs.m_size+1);
	int nRet = file.Read(pText,fs.m_size);
	file.Close();
/*
	�������һ������ļ��п��������룬������Ϊ��Ҫ�򿪵��ļ���unicode������������ANSI�ĸ�ʽ
	��ô����Ҫ�򿪵��ļ���ʲô��ʽ��
	�ü��±�����Ҫ�򿪵��ļ���Ȼ�����Ϊ����ͻῴ���������ļ���ʲô��ʽ���ˡ����������ΪANSI��ʽ
	�Ͳ�����������ˣ�
*/
	pText[nRet] = 0;//�������Ϊ0 ��β  �ַ�����βҪΪ\0;
	m_szCurrentFile = szFilePath;//�ѵ�ǰ�ļ�·������Ϊ��ǰ�򿪵��ļ�·��

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	pEdit->SetWindowText(pText);
	pEdit ->SetModify(FALSE);

	SetTitle();

}
//�����ļ��޸ĵ����
BOOL CNotePadDlg::Prompt()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_TEXT);
	if(pEdit->GetModify())//����ļ����޸�
	{
		CString str;
		if(m_szCurrentFile.IsEmpty())//�����ǰ���ļ�Ϊ�գ���str= �ޱ���
			str = "�ޱ���";
		else
			str = m_szCurrentFile; //������� ���ڴ��ļ���Path

		int nRet = MessageBox(str+"\r\n�Ѿ����޸ģ��Ƿ񱣴棿","��ʾ��Ϣ",
			MB_YESNOCANCEL|MB_ICONEXCLAMATION);

		if(IDCANCEL == nRet)//���ѡ����  ȡ������ô�����κδ���Ҳ���رնԻ���(���˳�������������)
			return FALSE;
		if(IDNO == nRet) //���ѡ���� �� ֱ�ӹرնԻ������˳���������������
			return TRUE;
		else//���ѡ���� �� �����ļ�
 			OnFileSave();
	}

	return TRUE;
}

//��������ı���
void CNotePadDlg::SetTitle()
{
	CString str;
	if(m_szCurrentFile.IsEmpty())
		str = "�ޱ���";
	else
		str = m_szCurrentFile;

	int i = str.ReverseFind('\\'); //�����ҵ� \\
	if(i > 0)
		str = str.Mid(i+1); //��\\λ�ô� �س�str���������

	SetWindowText(str);
}

//��ȡ������Ϣ
BOOL CNotePadDlg::PreTranslateMessage(MSG* pMsg)
{
	//��ȡ"="��
	if (pMsg->wParam ==	EQUAL)
	{
		CString str[3];
		
		/*��ȡ�����ַ�*/
		CString strText;
		//INT lastLine = editControl.GetLineCount()-1;    //���һ��

		/*��ȡ���������*/
		CPoint point = editControl.GetCaretPos();    //��ȡ�������ڿؼ���λ��
		INT cpxy = editControl.CharFromPos(point);    //��ȡ���λ��
		INT currentLine = HIWORD(cpxy);    //��ȡ�����к�
		/*
		char ch[10],ch2[10];
		itoa(currentLine, ch, 10);
		itoa(cpxy, ch2, 10);
		OutputDebugString(ch);
		OutputDebugString("\n");
		OutputDebugString(ch2);
		*/

		int len = editControl.LineLength(editControl.LineIndex(currentLine));    //��ȡ�г���
		editControl.GetLine(currentLine, strText.GetBuffer(len));
		strText.ReleaseBuffer(len);
		
		//���ֱ��ʽ�ֽ�ʽ��
		CString strRegex = "({[0-9]+}){[/*/+-//]}({[0-9]+})";
		CAtlRegExp<> reRule;
		REParseError status = reRule.Parse(strRegex);
		if (REPARSE_ERROR_OK != status)
		{ 
			return 0;
		}

		//�洢ƥ����
		CAtlREMatchContext<> mcRule;
		if (!reRule.Match(strText,&mcRule))
		{
			return 0;
		}
		for (UINT nGroupIndex = 0; nGroupIndex < mcRule.m_uNumGroups; ++nGroupIndex)
		{
			const CAtlREMatchContext<>::RECHAR* szStart = 0;
			const CAtlREMatchContext<>::RECHAR* szEnd = 0;
			mcRule.GetMatch(nGroupIndex, &szStart, &szEnd);

			ptrdiff_t nLength = szEnd - szStart;
			CString num(szStart, nLength);
			str[nGroupIndex] = num;
			//OutputDebugString((LPSTR)(LPCTSTR)num);
		}
		/*OutputDebugString(str[0]);
		OutputDebugString("\n");
		OutputDebugString(str[1]);*/
		DataOperate<CString> data(str[0], str[2]);
		INT operate = str[1].GetAt(0);    //��ȡ������
		char* result = nullptr;
		
		switch (operate)
		{
		case operators::ADD:
			result = data.Add();
			break;
		case operators::SUBTRACT:
			result = data.Subtract();
			break;
		case operators::MULTIPLY:
			result = data.Multiply();
			break;
		case operators::DEVIDE:
			result = data.Devide();
			break;
		}
		
		editControl.ReplaceSel("=");
		editControl.ReplaceSel(result);    //��������Edit Control��
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}