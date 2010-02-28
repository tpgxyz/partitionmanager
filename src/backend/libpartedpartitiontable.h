/***************************************************************************
 *   Copyright (C) 2010 by Volker Lanz <vl@fidra.de                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#if !defined(LIBPARTEDPARTITIONTABLE__H)

#define LIBPARTEDPARTITIONTABLE__H

#include "backend/corebackendpartitiontable.h"

#include "fs/filesystem.h"

#include <qglobal.h>

#include <parted/parted.h>

class CoreBackendPartition;
class Report;
class Partition;

class LibPartedPartitionTable : public CoreBackendPartitionTable
{
	public:
		LibPartedPartitionTable(PedDevice* device);
		~LibPartedPartitionTable();

	public:
		virtual bool open();

		virtual bool commit(quint32 timeout = 10);
		static bool commit(PedDisk* pd, quint32 timeout = 10);

		virtual CoreBackendPartition* getExtendedPartition();
		virtual CoreBackendPartition* getPartitionBySector(qint64 sector);

		virtual bool createPartition(Report& report, Partition& partition);
		virtual bool deletePartition(Report& report, Partition& partition);
		virtual bool updateGeometry(Report& report, Partition& partition, qint64 sector_start, qint64 sector_end);
		virtual bool clobberFileSystem(Report& report, Partition& partition);
		virtual bool resizeFileSystem(Report& report, Partition& partition, qint64 newLength);
		virtual FileSystem::Type detectFileSystemBySector(Report& report, Device& device, qint64 sector);

	private:
		PedDevice* pedDevice() { return m_PedDevice; }
		PedDisk* pedDisk() { return m_PedDisk; }

	private:
		PedDevice* m_PedDevice;
		PedDisk* m_PedDisk;
};

#endif
