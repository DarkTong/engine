#pragma once

#include <mutex>

#include "GZJRequire.h"
#include "GZJResourceManager.h"
#include "GZJResourceLoad.h"

namespace GZJ_ENGINE {

	class GZJResource {
	public:
		/** ��Դ��
		@param ����ǰ��Դ�Ĺ�����
		@param ��Դ�����·��
		*/
		GZJResource(GZJResourceManager* manager, const String& name, ResourceHandle handle);
	protected:
		/** ��Դ������
		*/
		GZJResourceManager* _mgr;
		/** ��Դ�洢·��
		*/
		String _path;
		/** ��Դ���
		*/
		ResourceHandle _handle;
		/** ��Դ����
		*/
		String _name;
		/** ��Դ״̬
		*/
		ResState _state;
		/** ��Դ���ü�����
		*/
		unsigned int _count;

	public:
		// ��Ԫ
		friend class GZJResourceManager;

	private:
		/** ������Դ״̬����
		*/
		mutable std::mutex mutexToState;

	public:
		/** ׼����Դ��׼������
		*/
		void Prepare();

		/** ͬ��������Դ
		*/
		void SyncLoad();

		/** �첽������Դ
		*/
		void AsyncLoad();

		/** ж����Դ
		*/
		void UnLoad();

		/** ������Դ״̬
		*/
		void SetState(ResState state);
		
		/** ��ȡ��Դ״̬
		*/
		ResState GetState() const;

		/** ��ȡ��Դ����
		*/
		virtual ResourceType GetResType() = 0;

		/** ��ȡ��Դ���
		*/
		ResourceHandle GetResHandle();

	private:
		// ���ڽӿ�

		/** ������Դ
		*/
		void Load();

		/** ʵ�м�����Դ
		*/
		virtual void DoLoad() = 0;

		/** ʵ��ж����Դ
		*/
		virtual void DoUnLoad() = 0;

		/** ǿ��ж����Դ
		* �����Ƿ��ж�����������
		* ���ڹ������ر�ʱ����
		*/
		void ForceUnLoad();
	};
}

